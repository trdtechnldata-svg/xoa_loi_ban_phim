#pragma once
#include <Arduino.h>
#include "charger1000_config.h"
namespace charger1000 {
#define APP_OFFSET_TRONG_FILE   0x4000UL    // 16 KB đầu là bootloader, KHÔNG gửi
#define HIEU_CHUAN_OFFSET       0x1F800UL   // từ đây là kho hiệu chuẩn, KHÔNG gửi
#define DIA_CHI_APP_DICH        0x08004000UL
#define DIA_CHI_HIEU_CHUAN_DICH 0x0801F800UL
#define KICH_THUOC_KHOI         1024UL      // 1 page flash

// =====================================================
// GIAO THỨC BOOTLOADER (đã giải mã từ firmware)
// ID gửi: host=6, thiết bị=9, mã giao thức 0xB0, byte thấp = lệnh
// ID trả: 0x0930B000 | trạng thái (8 = OK, 9 = lỗi), riêng version là 0x0930B003
// =====================================================
#define ID_GUI      0x0648B000UL
#define ID_PHAN_HOI 0x0930B000UL
#define LENH_XOA        0
#define LENH_DAT_KHOI   1
#define LENH_DU_LIEU    2
#define LENH_PHIEN_BAN  3
#define LENH_CHAY       5   // app: dữ liệu "IAP" = vào bootloader | bootloader: "APP" = chạy app
#define PHIEN_BAN_BOOT  "V0.02"

#define KHOANG_CACH_KHUNG_US 150
#define THU_LAI_KHOI         3


#ifndef CHI_HOI_PHIEN_BAN
#define CHI_HOI_PHIEN_BAN 0
#endif

enum MaLoi : uint8_t {
  LOI_KHONG = 0,
  LOI_FILE = 1,           // file trống / không hợp lệ
  LOI_CAN = 2,            // không khởi tạo / không gửi được khung
  LOI_KHONG_PHAN_HOI = 3, // board không trả lời lệnh hỏi version
  LOI_VAO_BOOT = 4,       // gửi lệnh IAP nhưng không vào được bootloader
  LOI_PHIEN_BAN_BOOT = 5, // bootloader khác V0.02
  LOI_XOA = 6,
  LOI_KHOI = 7,           // ghi khối thất bại sau khi thử lại
  LOI_CHAY = 8,           // gửi lệnh chạy nhưng app không trả lời
  LOI_BUS = 9             // bus lỗi, không ai ACK: sai chân TX/RX, sai tốc độ, chưa nối dây/GND
};

// prototype của các hàm lên đầu file, nếu struct nằm sau thì sẽ báo lỗi "not declared".
struct ThongTinPhienBan {
  char phienBan[6];
  bool laBootloader;   // true: "...IAP", false: "...APP"
};


extern int currentOption;
extern int screenState;
extern int targetScreen;
extern int progressVal;
extern uint8_t maLoiCuoi;
extern uint32_t diaChiFlashFileHienTai;
extern const uint32_t DIA_CHI_FILE_24;
extern const uint32_t DIA_CHI_FILE_15;
void hienThiManHinh();
bool napQuaCan(uint32_t diaChiFile);
}
