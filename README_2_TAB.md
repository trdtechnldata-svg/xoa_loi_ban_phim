# Giao diện xem pin: 2 tab

Áp dụng cho LFP 3.5 kW, B1, A1, LFP 2.4 kW, LFP 1.2 kW và JK BMS.

- Tab TONG QUAN: SOC, điện áp, dòng, dung lượng, cycle, SOH, AVG và nhiệt
  độ theo dữ liệu từng loại pin đang có. JK có thêm trạng thái MOS/cân bằng,
  công suất, thời gian chạy, lỗi và toàn bộ thông tin thiết bị/serial/SETUP PASS.
- Tab CELL PIN: các khung điện áp từng cell và Vmin/Vmax/DeltaV.
- JK dùng nút BLE trên thanh trên để mở danh sách Bluetooth, QUET khi đang
  trong danh sách, NGAT và HOME như trước. Không có thêm tab THIET BI hoặc
  tab Bluetooth trong thanh tab xem pin. Tổng quan JK có thanh cuộn bên
  phải vì nhiều thông số; vị trí cuộn riêng với danh sách Bluetooth.
- A1 hiện chỉ có số đo Vmin/Vmax/DeltaV, chưa có điện áp từng cell trong
  code nguồn. Tab Cell pin nói rõ chưa có dữ liệu từng cell, không tạo số giả.

## Cập nhật bản trước

Dành cho project xoa_loi_ban_phim2_JK_BMS.zip vừa được ghép JK riêng.
Chép đè/thêm 5 file vào cùng thư mục với xoa_loi_ban_phim.ino:

1. screens.c
2. battery_tabs.c (mới)
3. battery_tabs.h (mới)
4. jk_ui.cpp
5. xoa_loi_ban_phim.ino

Sau đó build/nạp lại như trước. Hoặc dùng toàn bộ gói project mới, giải nén
vào thư mục mới rồi mở xoa_loi_ban_phim.ino trong thư mục xoa_loi_ban_phim.
Không chép lẫn các module MK MỚI/reset của những bản cũ vào project này.

Giữ nguyên thư viện, User_Setup/TOUCH_CS, hiệu chuẩn TFT và chân CAN đang
chạy. Không đổi backlight, partition hay file firmware pin. Không có Wi-Fi,
MK MỚI, khôi phục mật khẩu hoặc reset BMS. Không thêm task/core.

## Phạm vi sửa

Dùng lại đúng các label mà code CAN đang cập nhật, chỉ thay parent và bố
cục; dữ liệu vẫn cập nhật khi tab tương ứng bị ẩn. Tab riêng không gửi lệnh
CAN/BLE và không đổi loại pin. BACK/HOME về launcher vẫn giữ.

Có sửa một lỗi đích hiển thị cũ trong hien_thi_b1(): dòng điện B1 trước
đang ghi nhầm vào nhãn LFP, nay ghi đúng objects.ampe_b1. Không thay dữ
liệu đầu vào, phép tính, khung CAN hoặc chu kỳ gửi/đọc.

Module battery_tabs.c phụ trách hai tab cho các trang CAN; jk_ui.cpp phụ
trách hai tab JK và danh sách BLE. Có thể sửa riêng hai module UI sau này.

## Kiểm tra

Đã biên dịch module C với LVGL 8.3.11 thật và kiểm tra 5 trang, toàn bộ
label liên kết, giới hạn viewport, cập nhật tab ẩn, 250 lần chuyển tab
không tăng widget. Đã dựng ảnh LVGL để kiểm tra không chồng chữ. UI JK /
HOME qua 21 vòng mở/đóng với ASan/UBSan, thanh cuộn Tổng quan và Bluetooth
độc lập; BLE picker không tự ngắt/quét khi chỉ mở danh sách.

Chưa build/link toàn bộ bằng ESP32 SDK và chưa nạp thử trên bo thật.
