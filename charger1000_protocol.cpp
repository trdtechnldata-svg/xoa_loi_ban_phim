// Protocol and flash-read core copied unchanged from the supplied source.
// Diagnostic wrappers preserve the original TWAI call arguments and results.
#include "charger1000_protocol.h"
#include "charger1000_diagnostics.h"
#include "esp_err.h"
#include "esp_heap_caps.h"
#include "esp_flash.h"
#include "driver/twai.h"
#include <string.h>
#define LOG(...) Serial.printf(__VA_ARGS__)
#define CAN_TX_PIN TOOL_CAN_TX
#define CAN_RX_PIN TOOL_CAN_RX
namespace charger1000 {
int currentOption = 1;
int screenState = 0;
int targetScreen = 0;
int progressVal = 0;
uint8_t maLoiCuoi = LOI_KHONG;
uint32_t diaChiFlashFileHienTai = 0x200000UL;
const uint32_t DIA_CHI_FILE_24 = 0x200000UL;
const uint32_t DIA_CHI_FILE_15 = 0x220000UL;

// Thin diagnostic wrappers: arguments, return values, wire data, timeout,
// retry count, and all original protocol function bodies below are unchanged.
static esp_err_t checkedDriverInstall(const twai_general_config_t *g,
                                    const twai_timing_config_t *t,
                                    const twai_filter_config_t *f) {
    const uint32_t caps = MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT;
    LOG("[CHARGER] CAN install: TX=%d RX=%d, queues=%u/%u, internal=%u largest=%u\n",
        CAN_TX_PIN, CAN_RX_PIN, (unsigned)g->tx_queue_len, (unsigned)g->rx_queue_len,
        (unsigned)heap_caps_get_free_size(caps), (unsigned)heap_caps_get_largest_free_block(caps));
    esp_err_t err = ::twai_driver_install(g,t,f);
    LOG("[CHARGER] CAN install result=%s (0x%lX)\n",esp_err_to_name(err),(unsigned long)(uint32_t)err);
    if (err != ESP_OK) setDiagnostic(DIAG_CAN_INSTALL,err);
    return err;
}
static esp_err_t checkedCanStart() {
    esp_err_t err = ::twai_start();
    LOG("[CHARGER] CAN start result=%s (0x%lX)\n",esp_err_to_name(err),(unsigned long)(uint32_t)err);
    if (err != ESP_OK) setDiagnostic(DIAG_CAN_START,err);
    return err;
}
static esp_err_t checkedTransmit(const twai_message_t *message, TickType_t wait) {
    esp_err_t err = ::twai_transmit(message,wait);
    if (err != ESP_OK) {
        setDiagnostic(DIAG_CAN_TX,err);
        LOG("[CHARGER] CAN TX id=0x%lX failed=%s (0x%lX)\n",
            (unsigned long)message->identifier,esp_err_to_name(err),(unsigned long)(uint32_t)err);
    }
    return err;
}
#define twai_driver_install(...) checkedDriverInstall(__VA_ARGS__)
#define twai_start(...) checkedCanStart(__VA_ARGS__)
#define twai_transmit(...) checkedTransmit(__VA_ARGS__)

static void be32(uint8_t *p, uint32_t v) {
  p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v;
}

// CRC-16/XMODEM (poly 0x1021, init 0) - đúng thuật toán bootloader dùng
static uint16_t crc16Xmodem(const uint8_t *p, uint32_t n) {
  uint16_t crc = 0;
  while (n--) {
    crc ^= (uint16_t)(*p++) << 8;
    for (int i = 0; i < 8; i++) crc = (crc & 0x8000) ? (uint16_t)((crc << 1) ^ 0x1021) : (uint16_t)(crc << 1);
  }
  return crc;
}

static bool docFileESP(uint32_t diaChiFile, uint32_t viTri, uint8_t *boDem, uint32_t doDai) {
  return esp_flash_read(esp_flash_default_chip, boDem, diaChiFile + viTri, doDai) == ESP_OK;
}

// Tìm byte khác 0xFF cuối cùng trong vùng app của file để biết độ dài app.
static bool tinhDoDaiApp(uint32_t diaChiFile, uint32_t &doDai) {
  static uint8_t b[KICH_THUOC_KHOI] __attribute__((aligned(4)));
  for (int32_t off = HIEU_CHUAN_OFFSET - KICH_THUOC_KHOI; off >= (int32_t)APP_OFFSET_TRONG_FILE; off -= KICH_THUOC_KHOI) {
    if (!docFileESP(diaChiFile, off, b, KICH_THUOC_KHOI)) return false;
    for (int i = KICH_THUOC_KHOI - 1; i >= 0; i--) {
      if (b[i] != 0xFF) { doDai = (uint32_t)off + i + 1 - APP_OFFSET_TRONG_FILE; return true; }
    }
  }
  return false;   // vùng app trống
}

// Kiểm tra file TRƯỚC khi gửi lệnh xóa.
static bool kiemTraFile(uint32_t diaChiFile, uint32_t doDai) {
  uint32_t v[2] __attribute__((aligned(4)));
  if (!docFileESP(diaChiFile, APP_OFFSET_TRONG_FILE, (uint8_t *)v, 8)) return false;
  uint32_t sp = v[0], rv = v[1];
  if ((sp & 0x2FFE0000UL) != 0x20000000UL) return false;          // SP phải nằm trong SRAM
  if (!(rv & 1)) return false;                                     // reset vector phải là Thumb
  uint32_t a = rv & ~1UL;
  if (a < DIA_CHI_APP_DICH || a >= DIA_CHI_HIEU_CHUAN_DICH) return false;
  uint32_t lam = (doDai + KICH_THUOC_KHOI - 1) & ~(KICH_THUOC_KHOI - 1);
  if (doDai < KICH_THUOC_KHOI || DIA_CHI_APP_DICH + lam > DIA_CHI_HIEU_CHUAN_DICH) return false;
  return true;
}

// =====================================================
// TẦNG CAN (TWAI, 250 kbps, khung mở rộng 29 bit)
// =====================================================
static bool khoiTaoCan() {
  twai_general_config_t g = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX_PIN, (gpio_num_t)CAN_RX_PIN, TWAI_MODE_NORMAL);
  g.tx_queue_len = 32;
  g.rx_queue_len = 256;   // bus sạc có nhiều khung khác, hàng đợi nhận phải đủ lớn
  twai_timing_config_t t = TWAI_TIMING_CONFIG_250KBITS();
  twai_filter_config_t f = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  if (twai_driver_install(&g, &t, &f) != ESP_OK) return false;
  if (twai_start() != ESP_OK) { twai_driver_uninstall(); return false; }
  return true;
}

// Tắt hẳn TWAI sau khi nạp để ESP không tham gia bus khi rảnh.
static void tatCan() {
  twai_stop();
  twai_driver_uninstall();
}

static void phucHoiCan() {
  twai_status_info_t s;
  twai_get_status_info(&s);
  if (s.state == TWAI_STATE_BUS_OFF) {
    twai_initiate_recovery();
    uint32_t bd = millis();
    while (millis() - bd < 1500) {
      twai_get_status_info(&s);
      if (s.state == TWAI_STATE_STOPPED) break;
      delay(10);
    }
  }
  twai_get_status_info(&s);
  if (s.state == TWAI_STATE_STOPPED) twai_start();
  twai_clear_transmit_queue();
  twai_clear_receive_queue();
}

// --- Chẩn đoán bus: phân biệt "không ai ACK" (E9) với "bus sống nhưng không ai trả lời" (E3)
static uint32_t g_khungLa = 0;      // số khung khác thấy trên bus trong lúc chờ phản hồi
static uint32_t g_tecCaoNhat = 0;   // tx_error_counter lớn nhất đã thấy
static uint32_t g_loiBus = 0;       // bus_error_count lớn nhất đã thấy
static bool g_busOff = false;

static void ghiNhanTrangThaiBus() {
  twai_status_info_t s;
  twai_get_status_info(&s);
  if (s.tx_error_counter > g_tecCaoNhat) g_tecCaoNhat = s.tx_error_counter;
  if (s.bus_error_count > g_loiBus) g_loiBus = s.bus_error_count;
  if (s.state == TWAI_STATE_BUS_OFF) g_busOff = true;
}

// Gọi khi không nhận được phản hồi version. Một node đứng một mình (không ai ACK)
// sẽ có tx_error_counter lên tới ~128 và bus_error_count tăng.
static uint8_t phanLoaiKhongPhanHoi() {
  LOG("Khong phan hoi: TEC=%lu busErr=%lu busOff=%d khungLa=%lu\n",
      (unsigned long)g_tecCaoNhat, (unsigned long)g_loiBus, (int)g_busOff, (unsigned long)g_khungLa);
  if (g_busOff || g_tecCaoNhat >= 96 || g_loiBus > 0) return LOI_BUS;
  return LOI_KHONG_PHAN_HOI;
}

static bool guiKhung(uint8_t lenh, const uint8_t *du, uint8_t dlc) {
  twai_message_t m = {};
  m.extd = 1;
  m.identifier = ID_GUI | lenh;
  m.data_length_code = dlc;
  for (uint8_t i = 0; i < dlc; i++) m.data[i] = du[i];
  return twai_transmit(&m, pdMS_TO_TICKS(200)) == ESP_OK;
}

// Chờ khung trạng thái của bootloader: 8 = OK, 9 = lỗi, 0 = hết giờ.
static int nhanTrangThai(uint32_t timeoutMs) {
  uint32_t bd = millis();
  twai_message_t m;
  while (millis() - bd < timeoutMs) {
    if (twai_receive(&m, pdMS_TO_TICKS(10)) == ESP_OK && m.extd && !m.rtr) {
      if (m.identifier == (ID_PHAN_HOI | 8)) return 8;
      if (m.identifier == (ID_PHAN_HOI | 9)) return 9;
    }
  }
  return 0;
}

static bool hoiPhienBan(ThongTinPhienBan &tt, uint32_t timeoutMs) {
  twai_clear_receive_queue();
  if (!guiKhung(LENH_PHIEN_BAN, nullptr, 0)) { ghiNhanTrangThaiBus(); return false; }
  uint32_t bd = millis();
  twai_message_t m;
  while (millis() - bd < timeoutMs) {
    if (twai_receive(&m, pdMS_TO_TICKS(10)) == ESP_OK) {
      if (m.extd && !m.rtr && m.identifier == (ID_PHAN_HOI | LENH_PHIEN_BAN) && m.data_length_code >= 8) {
        memcpy(tt.phienBan, m.data, 5);
        tt.phienBan[5] = 0;
        tt.laBootloader = (m.data[5] == 'I');
        return true;
      }
      if (g_khungLa++ < 5) LOG("Khung la: id=0x%lX ext=%d dlc=%d\n", (unsigned long)m.identifier, (int)m.extd, (int)m.data_length_code);
    }
  }
  ghiNhanTrangThaiBus();
  return false;
}

static bool hoiPhienBanThuLai(ThongTinPhienBan &tt, int soLan, uint32_t timeoutMs) {
  for (int i = 0; i < soLan; i++) {
    if (hoiPhienBan(tt, timeoutMs)) return true;
    phucHoiCan();
  }
  return false;
}

// =====================================================
// CÁC BƯỚC NẠP
// =====================================================
static uint8_t vaoBootloader(ThongTinPhienBan &tt) {
  if (!hoiPhienBanThuLai(tt, 3, 300)) return phanLoaiKhongPhanHoi();
  LOG("Version: %s (%s)\n", tt.phienBan, tt.laBootloader ? "BOOT" : "APP");
  if (tt.laBootloader) return LOI_KHONG;

  // Đang ở app: gửi lệnh 5 + "IAP" -> app xóa cờ boot và reset vào bootloader
  const uint8_t iap[3] = {'I', 'A', 'P'};
  if (!guiKhung(LENH_CHAY, iap, 3)) return LOI_CAN;
  delay(1500);
  for (int i = 0; i < 10; i++) {
    phucHoiCan();
    if (hoiPhienBan(tt, 300) && tt.laBootloader) { LOG("Da vao bootloader %s\n", tt.phienBan); return LOI_KHONG; }
    delay(300);
  }
  return LOI_VAO_BOOT;
}

static uint8_t napMotKhoi(uint32_t diaChiFile, uint32_t chiSoKhoi, uint32_t doDaiApp) {
  static uint8_t blk[KICH_THUOC_KHOI + 2] __attribute__((aligned(4)));
  uint32_t viTri = chiSoKhoi * KICH_THUOC_KHOI;
  memset(blk, 0xFF, KICH_THUOC_KHOI);
  uint32_t soByte = (doDaiApp - viTri < KICH_THUOC_KHOI) ? (doDaiApp - viTri) : KICH_THUOC_KHOI;
  if (!docFileESP(diaChiFile, APP_OFFSET_TRONG_FILE + viTri, blk, soByte)) return LOI_FILE;
  uint16_t crc = crc16Xmodem(blk, KICH_THUOC_KHOI);
  blk[KICH_THUOC_KHOI] = crc >> 8;        // byte cao trước
  blk[KICH_THUOC_KHOI + 1] = crc & 0xFF;
  const uint32_t tong = KICH_THUOC_KHOI + 2;

  for (int lan = 0; lan < THU_LAI_KHOI; lan++) {
    uint8_t h[8];
    be32(h, viTri);       // offset tính từ 0x08004000
    be32(h + 4, tong);    // độ dài khối, đã gồm 2 byte CRC
    if (!guiKhung(LENH_DAT_KHOI, h, 8)) { phucHoiCan(); continue; }
    if (nhanTrangThai(500) != 8) { phucHoiCan(); continue; }

    bool loiGui = false;
    for (uint32_t i = 0; i < tong; i += 8) {
      uint8_t n = (tong - i < 8) ? (uint8_t)(tong - i) : 8;
      // Trước khung cuối: xả hàng đợi nhận để khung trả lời không bị tràn bởi các khung khác trên bus
      if (i + 8 >= tong) twai_clear_receive_queue();
      if (!guiKhung(LENH_DU_LIEU, blk + i, n)) { loiGui = true; break; }
      delayMicroseconds(KHOANG_CACH_KHUNG_US);
    }
    if (loiGui) { phucHoiCan(); continue; }

    int tt = nhanTrangThai(2000);   // bootloader ghi flash + kiểm CRC rồi mới trả lời
    if (tt == 8) return LOI_KHONG;
    LOG("Khoi %lu lan %d: trang thai %d\n", (unsigned long)chiSoKhoi, lan, tt);
    phucHoiCan();
  }
  return LOI_KHOI;
}

static uint8_t chayQuaTrinhNap(uint32_t diaChiFile, uint32_t doDaiApp) {
  ThongTinPhienBan tt;
  progressVal = 2; hienThiManHinh();
#if CHI_HOI_PHIEN_BAN
  if (!hoiPhienBanThuLai(tt, 3, 300)) return phanLoaiKhongPhanHoi();
  LOG("Version: %s (%s)\n", tt.phienBan, tt.laBootloader ? "BOOT" : "APP");
  progressVal = 100;
  return LOI_KHONG;
#endif
  uint8_t l = vaoBootloader(tt);
  if (l) return l;
  if (strcmp(tt.phienBan, PHIEN_BAN_BOOT) != 0) return LOI_PHIEN_BAN_BOOT;

  uint32_t doDaiLam = (doDaiApp + KICH_THUOC_KHOI - 1) & ~(KICH_THUOC_KHOI - 1);

  // XÓA: bootloader xóa page cờ 0x08003C00 rồi các page từ 0x08004000 tới địa chỉ cuối (gồm cả page chứa nó).
  // Truyền doDaiLam-1 để chỉ xóa đúng các page cần dùng.
  progressVal = 5; hienThiManHinh();
  uint8_t d[4];
  be32(d, doDaiLam - 1);
  if (!guiKhung(LENH_XOA, d, 4)) return LOI_CAN;
  if (nhanTrangThai(15000) != 8) return LOI_XOA;
  progressVal = 10; hienThiManHinh();

  uint32_t soKhoi = doDaiLam / KICH_THUOC_KHOI;
  for (uint32_t k = 0; k < soKhoi; k++) {
    uint8_t kq = napMotKhoi(diaChiFile, k, doDaiApp);
    if (kq) return kq;
    progressVal = 10 + (int)((k + 1) * 90UL / soKhoi);
    hienThiManHinh();
    yield();
  }

  // CHẠY APP rồi xác nhận app trả lời version
  const uint8_t app[3] = {'A', 'P', 'P'};
  if (!guiKhung(LENH_CHAY, app, 3)) return LOI_CAN;
  delay(2000);
  for (int i = 0; i < 10; i++) {
    phucHoiCan();
    if (hoiPhienBan(tt, 500) && !tt.laBootloader) { LOG("App chay: %s\n", tt.phienBan); progressVal = 100; return LOI_KHONG; }
    delay(500);
  }
  return LOI_CHAY;
}

bool napQuaCan(uint32_t diaChiFile) {
  uint32_t doDai = 0;
  if (!tinhDoDaiApp(diaChiFile, doDai) || !kiemTraFile(diaChiFile, doDai)) { maLoiCuoi = LOI_FILE; return false; }
  LOG("App: %lu byte\n", (unsigned long)doDai);
  if (!khoiTaoCan()) { maLoiCuoi = LOI_CAN; return false; }
  g_khungLa = 0; g_tecCaoNhat = 0; g_loiBus = 0; g_busOff = false;
  maLoiCuoi = chayQuaTrinhNap(diaChiFile, doDai);
  tatCan();
  return maLoiCuoi == LOI_KHONG;
}


} // namespace charger1000
