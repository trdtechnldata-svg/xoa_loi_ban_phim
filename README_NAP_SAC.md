# Nạp sạc 1000W qua CAN

Chức năng mới dùng **TX GPIO17, RX GPIO16, CAN 250 kbps** của máy xóa lỗi.
Đích vẫn phải có bootloader IAP **V0.02** tương thích với code anh cung cấp.
Tên lựa chọn **Pin 2.4 / Pin 1.5** được giữ đúng nội dung OLED, không tự đổi tên firmware.

## 1. Chuẩn bị project

Dùng toàn bộ thư mục này, bao gồm các file `charger1000*`, `ui_decor*` và
`partitions.csv`. Giữ cấu hình TFT_eSPI, cảm ứng và LVGL đang chạy được.
Các thư viện của máy vẫn như trước; không cần U8g2.
Bản tích hợp hướng tới ESP32/core 2.0.7 và driver TWAI legacy như log thư viện
anh đã gửi. Chưa kiểm tra build với phiên bản core/thư viện khác.

`partitions.csv` dành cho flash **4 MB trở lên**, không OTA. Nó giữ hai slot
firmware đúng địa chỉ của code OLED:

| Vùng | Địa chỉ ESP32 | Kích thước |
|---|---:|---:|
| NVS | `0x9000` | `0x5000` |
| OTA data dự trữ | `0xE000` | `0x2000` |
| Chương trình máy xóa lỗi | `0x10000` | `0x1F0000` |
| `fw24`: Pin 2.4 | `0x200000` | `0x20000` |
| `fw15`: Pin 1.5 | `0x220000` | `0x20000` |
| SPIFFS | `0x240000` | `0x1C0000` |

Arduino ESP32 nhận `partitions.csv` trong cùng thư mục sketch. Khi IDE kiểm
tra kích thước dựa trên mục Partition Scheme được chọn, chọn mục cho phép
APP ít nhất khoảng 2 MB; **APP thực tế phải không quá `0x1F0000` byte**.
File CSV trong project mới là bảng phân vùng thực sự cần nạp.

**SPIFFS chuyển vị trí so với nhiều cấu hình mặc định.** Sao lưu nội dung
SPIFFS cũ nếu cần dùng lại. Code máy có `SPIFFS.begin(true)`, có thể định dạng
vùng SPIFFS mới khi không nhận ra hệ thống file. NVS/EEPROM vẫn ở vùng cũ.
Không bật xóa toàn bộ flash khi chỉ cập nhật sketch và muốn giữ hai firmware.

## 2. Hai file firmware đích chưa có trong gói

File TXT anh gửi chỉ chứa chương trình nạp và địa chỉ lưu file, không chứa
byte firmware sạc. Cần hai BIN đầy đủ **128 KiB = 131072 byte**, tương ứng
với ảnh flash đích từ `0x08000000`. Không dùng BIN chỉ chứa vùng APP.
Có thể chỉ lưu một lựa chọn nếu hiện có một firmware.

Khi nạp, code giữ nguyên cách đọc của bản gốc:

- Bỏ `0x4000` byte bootloader đầu file.
- Chỉ quét/gửi APP từ `0x4000` đến trước `0x1F800` trong file.
- Không gửi vùng hiệu chuẩn `0x1F800–0x1FFFF`.
- Kiểm tra SP/reset vector và độ dài APP trước khi gửi lệnh xóa.

Nếu thiếu file/slot hoặc file không hợp lệ: **FAILED E1**, không xóa đích.
Bản tích hợp còn kiểm tra partition `fw24`/`fw15` đúng địa chỉ/kích thước
trước khi cho lõi giao thức đọc flash thô.

## 3. Ghi firmware vào ESP32

Nạp sketch cùng bảng phân vùng mới trước. Đóng Serial Monitor.
Công cụ Python chỉ ghi file sạc vào ESP32; chưa gửi lệnh nạp tới sạc.
Nó đọc và kiểm tra partition table của ESP32 trước khi ghi để tránh đè APP/SPIFFS.

Kiểm tra file, chưa ghi gì:

```powershell
py tools\load_firmware.py --pin24 firmware_pin24.bin --pin15 firmware_pin15.bin
```

Để ghi qua USB, dùng esptool 4.x (ví dụ bản 4.5.1), thay `COM5` bằng cổng máy:

```powershell
py -m pip install esptool==4.5.1
py tools\load_firmware.py --write --port COM5 --pin24 firmware_pin24.bin --pin15 firmware_pin15.bin
```

Hoặc chỉ ghi một file:

```powershell
py tools\load_firmware.py --write --port COM5 --pin24 firmware_pin24.bin
```

Công cụ xác thực kích thước BIN, vector APP và biên vùng nạp. SHA-256 được
in ra để đối chiếu đúng file; nó không tự chứng minh firmware phù hợp với
mẫu sạc. Dùng đúng file đã thử với chương trình OLED của anh.

## 4. Thao tác trên TFT

1. Mở ứng dụng **Nap 1000W**.
2. `NEXT` đổi giữa `1. Pin 2.4` và `2. Pin 1.5`; chạm trực tiếp vào thẻ cũng chọn được.
3. `SELECT` bắt đầu nạp lựa chọn hiện tại.
4. Màn hình hiển thị `CAN 2.4...` hoặc `CAN 1.5...`, phần trăm và thanh tiến trình.
5. Chỉ sau khi gửi `APP` và hỏi version xác nhận app đang chạy mới báo
   `PIN 2.4 OK` / `PIN 1.5 OK` và `>>>SUCCESS`.
6. Nếu lỗi, hiện `FAILED E<n>` giống OLED. `NEXT` hoặc `SELECT` quay lại menu.
7. `BACK` quay về trang ứng dụng và khôi phục CAN 250 kbps của máy xóa lỗi.

Trong lúc nạp, NEXT/SELECT/BACK bị khóa. Không thêm hủy giữa lúc xóa/ghi
vì code gốc không có cơ chế đó. Phiên nạp chạy đồng bộ trong loop như code
OLED; callback hiển thị cập nhật TFT trực tiếp. Không tạo worker/queue hay
dành thêm stack riêng. Trang nạp vẽ trực tiếp lên root màn hình home, không tạo thêm
widget khi mở. Chạm được thu nhận từ callback đọc cảm ứng của máy, sau đó
xử lý ở vòng lặp chính; các ứng dụng gốc được ẩn tạm và khôi phục khi BACK.
Lần chạm BACK được giữ lại đến khi nhả tay để không bấm xuyên sang home.

## 5. Giao thức giữ nguyên

| Mục | Giá trị |
|---|---|
| CAN gửi | `0x0648B000 OR lệnh`, extended 29 bit |
| Version | Gửi lệnh 3; nhận `0x0930B003` |
| Vào boot | Lệnh 5, dữ liệu `IAP` |
| Xóa | Lệnh 0, BE32(độ dài APP làm tròn 1024 − 1) |
| Đặt khối | Lệnh 1, BE32(offset từ APP) + BE32(1026) |
| Dữ liệu | Lệnh 2, 1024 byte (đệm FF) + CRC16/XMODEM, byte cao trước |
| Trả trạng thái | `0x0930B008` OK, `0x0930B009` lỗi |
| Chạy APP | Lệnh 5, dữ liệu `APP`, sau đó kiểm tra version |
| Khoảng cách khung dữ liệu | 150 µs theo lời gọi gốc |
| Thử lại khối | Tối đa 3 lần |
| Thử lại toàn phiên | Thêm 1 lần khi thất bại, trừ E1 |
| Chờ ACK header / ghi khối / xóa | 500 / 2000 / 15000 ms |

`charger1000_protocol.cpp` chứa nguyên văn các hàm từ `be32` đến hết
`napQuaCan` của nguồn gửi kèm, thêm namespace/include, ánh xạ chân và wrapper chẩn đoán quanh các lời gọi
TWAI. Các wrapper truyền nguyên đối số/timeout, trả nguyên kết quả và chỉ
in log/ghi lý do lỗi; không đổi payload hay nhánh retry của giao thức.
Nguồn OLED tham chiếu nằm ở `docs/REFERENCE_CAN_FLASHER_OLED.txt`.
Phần ngoài lõi chỉ chuyển UI, bàn giao CAN, kiểm tra slot và chạy tác vụ nạp.

## 6. Mã lỗi

| Mã | Ý nghĩa theo nguồn |
|---|---|
| E1 | File APP rỗng/không hợp lệ; trong bản tích hợp cũng dùng khi thiếu/sai slot firmware |
| E2 | Lỗi khởi tạo/gửi CAN hoặc bàn giao/khôi phục CAN thất bại |
| E3 | Không nhận phản hồi version |
| E4 | Không vào được bootloader |
| E5 | Bootloader khác V0.02 |
| E6 | Xóa không thành công |
| E7 | Ghi khối thất bại sau thử lại |
| E8 | Chạy APP nhưng chưa xác nhận APP trả lời |
| E9 | Chẩn đoán bus lỗi/không ACK như code gốc |

Log vẫn theo Serial của máy: **9600 baud**.

Tham khảo API nền tảng:
- https://docs.espressif.com/projects/arduino-esp32/en/latest/tutorials/partition_table.html
- https://github.com/handmade0octopus/ESP32-TWAI-CAN

## 7. Bản sửa mở trang bị load lại

Bản trước tạo thêm một screen và các nút/nhãn/thanh tiến trình khi mở lần đầu.
Project đã giữ hơn 500 widget, nên cần loại bỏ phần cấp phát tăng thêm để
tránh gây áp lực lên heap LVGL. Đây là điểm rủi ro xác định từ code; chưa có
log bo thật để xác nhận nguyên nhân reset cụ thể.

Bản này sử dụng root home sẵn có, vẽ bằng draw callback và điều khiển bằng
hit-test cảm ứng. Không xóa hay tạo lại các widget chức năng cũ. Mỗi phần tử
home được khôi phục đúng cờ HIDDEN ban đầu khi thoát. Giao thức nạp, địa chỉ
file, CRC, timeout và retry vẫn giữ nguyên.

Nếu còn reset, mở Serial Monitor 9600 baud và gửi log từ khi boot đến sau
khi bấm Nap 1000W, gồm Guru Meditation/Backtrace nếu có.

## 8. Bản cập nhật khi báo chỉ hiện nửa màn hình

Bản này bỏ worker có stack riêng 6144 byte của bản trước, chạy đồng bộ như
nguồn OLED. Không cấp phát thêm task, queue hoặc framebuffer toàn màn hình.
Bộ đệm LVGL vẫn là 480 × 20 pixel; mỗi lần vẽ toàn màn hình dùng lại bộ
đệm cho 16 dải, phủ đủ 480 × 320 pixel. Dùng RGB565 (`LV_COLOR_DEPTH=16`).
Bỏ `initDMA()` vì flush dùng `pushColors()` đồng bộ, không dùng DMA.
Yêu cầu vẽ lại toàn màn sau setup và khi mở/đóng trang nạp; tiến trình nạp
được refresh trực tiếp từ callback hiển thị của giao thức.

Chưa có ảnh/log bo để kết luận nguyên nhân nửa màn đen. Serial 9600 baud:

- `[DISPLAY] TFT=480x320, UI=480x320, color=16-bit, buffer=20 rows`.
- Nếu SIZE MISMATCH: kiểm tra lại User_Setup và rotation của TFT_eSPI theo
  bản cũ đã chạy; không tự đổi chân màn hình theo cấu hình bo khác.
- Ba lượt refresh đầu in số dải, số pixel và `bottom`; một lượt toàn màn
  phải tới `bottom=319`. Lượt cập nhật một vùng nhỏ có thể có giá trị thấp hơn.
- `[CHARGER] Loop stack minimum before/after` đo stack vòng lặp khi nạp.

Nếu còn nửa màn đen, gửi ảnh toàn màn, các dòng DISPLAY và cho biết xảy ra
ngay trang chủ hay chỉ khi mở Nap 1000W. Không suy ra nguyên nhân chỉ từ
`LVGL free=0`: bộ theo dõi này không phản ánh heap khi dùng custom allocator.

FAILED E2 vẫn có lý do CAN INSTALL, CAN START, CAN TX, CAN RELEASE hoặc
CAN RESTORE kèm mã. Nếu còn E2, gửi từ SELECT đến Session finished.
Không đổi queue TX32/RX256, ID CAN, CRC, địa chỉ, khối hay timeout nguồn.
