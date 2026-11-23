# JK BMS tích hợp vào máy xóa lỗi

Bản này sửa trực tiếp từ xoa_loi_ban_phim2.rar người dùng gửi. Launcher và
các ứng dụng khác được giữ. Bấm JK BMS mở giao diện native TFT giống project
JK_BMS_ONLY, không còn vào màn JK LVGL cũ.

## Nạp và dùng

1. Giải nén toàn bộ gói vào thư mục mới, mở xoa_loi_ban_phim.ino nằm trong
   thư mục xoa_loi_ban_phim. Không chép các file MK MỚI cũ vào đây.
2. Giữ TFT_eSPI User_Setup và hiệu chuẩn cảm ứng/chân màn hình đang chạy.
   Rotation=1, 480x320, backlight GPIO27. Không khởi tạo thêm driver TFT.
3. Dùng bộ thư viện của máy: LVGL 8.3.11, TFT_eSPI 2.3.70,
   NimBLE-Arduino 2.5.0, ESP32 core 2.0.7 và ESP32-TWAI-CAN đang dùng.
4. Giữ partitions.csv. Chọn Erase All Flash = Disabled để giữ các vùng bin
   sạc nếu đã nạp riêng. Firmware pin24 và các file nguồn nạp sạc giữ nguyên.
5. Build và nạp lại như trước. Serial Monitor 9600 baud.
6. Từ launcher bấm JK BMS -> Bluetooth tự quét -> bấm đúng tên/MAC để nối.
   Thanh bên phải có núm kéo, chạm rãnh và mũi tên bấm/giữ để cuộn.

## Giao diện JK

- Hai tab xem pin: TONG QUAN và CELL PIN.
- TONG QUAN có thanh cuộn phải để xem tất cả thông số và thông tin thiết bị,
  serial, SETUP PASS nếu BMS trả trường này.
- CELL PIN có các ô cell cùng Vmin/Vmax/DeltaV.
- Nút BLE mở danh sách thiết bị riêng; trong danh sách có QUET, NGAT,
  thanh cuộn và FRAME JK02-24S/32S. Danh sách không phải tab xem pin thứ ba.
- HOME ở góc trên phải về launcher. Không có MK MỚI, reset hoặc Wi-Fi.

## Vào/thoát không chồng luồng cũ

BLE chỉ khởi tạo ở lần đầu mở JK, không tự quét/kết nối lúc bật máy.
Module có một task I/O không pin core, sử dụng lại cho các lần mở sau.
Callback không vẽ màn hình và không dùng con trỏ scan đã hết vòng đời.
Kết nối, subscribe và parser dùng bản JK riêng, chỉ gửi lệnh đọc 96/97.

Khi mở JK, vòng lặp native sở hữu TFT/cảm ứng; không chạy legacy CAN/LVGL
song song trên màn hình đó. Khi HOME, hủy lệnh đang chờ trong queue và
các lần thử tiếp theo; worker dừng scan/ngắt liên kết khi lời gọi BLE hiện
thời trả về. HOME không chờ thao tác GATT. LVGL được reset trạng thái chạm
và vẽ lại toàn bộ màn hình chính. Giữ lọc nhả chạm để tránh bấm xuyên từ
launcher sang danh sách hoặc từ HOME sang ứng dụng dưới ngón tay.

Bỏ cấp phát cây widget JK LVGL cũ không còn dùng để dành RAM cho BLE.
Không chia hai core, không đổi chân CAN hay giao thức nạp sạc.

## Sửa module sau này

| File | Phụ trách |
|---|---|
| jk_app.cpp / .h | mở/đóng ứng dụng, cảm ứng và bàn giao màn hình |
| jk_ui.cpp / .h | hai tab xem pin, ô cell, Bluetooth/thanh cuộn, HOME |
| jk_ble.cpp / .h | scan, chọn MAC, nối/ngắt, retry, tạm dừng khi thoát |
| jk_protocol.cpp / .h | ghép frame/checksum, giải mã JK02-24S/32S |
| jk_types.h | dữ liệu trao đổi giữa BLE và UI |
| jk_display.cpp / .h | dùng chung TFT của máy, không begin lại |
| jk_config.h | cấu hình JK, không thay cấu hình CAN của máy |

Sau khi thay module vẫn phải biên dịch/nạp sketch. Không cần đóng gói lại
các firmware bin hoặc file ảnh nếu chỉ sửa module JK.

## Kiểm tra và giới hạn

Đã kiểm tra UI native, worker BLE và vòng đời HOME trên host ASan/UBSan;
đã biên dịch phần C giao diện và chạy bàn giao launcher/HOME với LVGL
8.3.11 thật. Các nguồn CAN, Speed Up, nạp sạc, partition, ảnh và bin được
đối chiếu nguyên byte với gói gốc. Chi tiết docs/JK_INTEGRATION_VALIDATION.md.

Chưa build/link toàn bộ project bằng ESP32 SDK trong phiên này, chưa nạp
bo/màn hình/BMS thật. Chưa đo heap thực tế khi mở BLE sau các ứng dụng
khác. Không kèm BIN build với chân màn hình giả.
