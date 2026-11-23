MÁY XÓA LỖI — CẬP NHẬT HIỂN THỊ TFT

Dùng toàn bộ thư mục project, mở xoa_loi_ban_phim.ino; không chỉ chép file .ino.
Giữ User_Setup TFT_eSPI, chân cảm ứng và cấu hình LVGL đã chạy ở bản cũ.
LVGL phải dùng LV_COLOR_DEPTH=16 để truyền RGB565 tới TFT_eSPI.
Không bật Erase All Flash nếu cần giữ hai firmware đã ghi vào hai slot.

BẢN CẬP NHẬT
- Bỏ worker và stack riêng 6144 byte; chạy nạp đồng bộ như nguồn OLED.
- Giữ bộ đệm 480 x 20 pixel, tái sử dụng qua 16 dải để vẽ đủ 480 x 320.
- Không cấp phát framebuffer toàn màn, không tạo thêm widget khi mở trang nạp.
- Bỏ initDMA không dùng; truyền TFT đồng bộ qua pushColors như bản gốc.
- Yêu cầu refresh toàn màn sau setup và khi mở/đóng Nap 1000W.
- Thêm log kích thước TFT, số dải/pixel và dòng cuối của ba lượt refresh đầu.

CHẨN ĐOÁN
Serial Monitor 9600 baud. Kích thước mong đợi:
[DISPLAY] TFT=480x320, UI=480x320, color=16-bit, buffer=20 rows
Lượt vẽ toàn màn phải tới bottom=319 (cập nhật một vùng nhỏ có thể thấp hơn).
Nếu SIZE MISMATCH: đối chiếu User_Setup/rotation với bản cũ đã chạy.
Nếu vẫn nửa dưới đen: gửi ảnh toàn màn, log DISPLAY, và cho biết trang chủ
hay trang nạp bị lỗi. Chưa xác nhận nguyên nhân hoặc kết quả trên bo thật.

Chức năng, dữ liệu, callback chẩn đoán và lõi giao thức CAN vẫn giữ nguyên.
Giao diện LVGL 8.3 + TFT_eSPI; không cần mở EEZ Studio, không cần OLED/U8g2.
Trang Nap 1000W vẽ trên root có sẵn, ẩn tạm các nút home và khôi phục khi BACK.
NEXT/SELECT/BACK bị khóa khi nạp; chỉ thoát sau khi phiên nạp kết thúc.
CAN: TX GPIO17, RX GPIO16; 250 kbps; giao thức nạp extended 29 bit.

Giữ nội dung OLED: Pin 2.4 / Pin 1.5, CAN 2.4... / CAN 1.5...,
phần trăm, PIN 2.4 OK / PIN 1.5 OK, >>>SUCCESS, FAILED E1...E9.
FAILED E2 có dòng phụ CAN INSTALL/START/TX/RELEASE/RESTORE và mã lỗi.
Nếu còn E2, gửi log từ [CHARGER] SELECT đến Session finished.
LVGL free=0 khi dùng custom allocator chưa chứng minh hết RAM.

README_NAP_SAC.md có hướng dẫn phân vùng và ghi hai firmware tại
0x200000 / 0x220000. Hai BIN đích chưa có trong đầu vào, không kèm trong gói.
Không thay đổi phân vùng hoặc định dạng file so với bản tích hợp trước.
Ảnh UI_PREVIEW.png chỉ mô phỏng bố cục, không phải ảnh thiết bị thật.

Đã kiểm thử bằng API mô phỏng trên PC; chưa build đầy đủ với bộ thư viện
Arduino của anh, chưa kiểm tra màn hình/bus CAN hoặc nạp sạc thật.
Chi tiết: docs/VALIDATION.md.
