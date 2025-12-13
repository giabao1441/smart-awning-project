# HƯỚNG DẪN LẮP ĐẶT HỆ THỐNG BẠT XẾP THÔNG MINH

## BƯỚC 1: CHUẨN BỊ VÀ KIỂM TRA

### 1.1 Kiểm tra hệ thống bạt hiện tại
- [ ] Xác định loại motor (AC/DC)
- [ ] Tìm vị trí hộp điều khiển 3 nút
- [ ] Test 3 nút: KÉO, THU, STOP
- [ ] Đo điện áp tín hiệu điều khiển (thường 12V/24V)
- [ ] Chụp ảnh sơ đồ đấu dây hiện tại

### 1.2 Chọn vị trí lắp đặt
- [ ] **Arduino box**: Gần hộp điều khiển cũ, tránh ẩm
- [ ] **Cảm biến mưa**: Nơi tiếp xúc trực tiếp với mưa
- [ ] **Limit switches**: Đầu và cuối hành trình bạt
- [ ] **LED RGB**: Vị trí dễ quan sát
- [ ] **Nút smart mode**: Gần nút điều khiển cũ

## BƯỚC 2: LẮP ĐẶT PHẦN CỨNG

### 2.1 Lắp đặt cảm biến mưa
```bash
Vị trí lý tưởng:
- Cao hơn bạt khoảng 50cm
- Không bị che chắn 
- Dây kéo về Arduino < 5m
- Có thể vệ sinh dễ dàng

Cách lắp:
1. Khoan lỗ đường kính 6mm
2. Dùng ốc vít inox M5 cố định
3. Seal chống nước bằng silicon
4. Kéo dây 3 core về hộp Arduino
```

### 2.2 Lắp đặt limit switches
```bash
Limit Switch 1 (vị trí KÉO HẾT):
- Gắn trên ray bạt, vị trí cuối
- Khi bạt kéo hết → switch được nhấn
- Cách đấu: NO contact

Limit Switch 2 (vị trí THU HẾT):  
- Gắn gần motor/drum cuốn bạt
- Khi bạt thu hết → switch được nhấn
- Cách đấu: NO contact
```

### 2.3 Lắp đặt LED RGB và nút Smart Mode
```bash
LED RGB:
- Gắn ở vị trí dễ nhìn từ trong nhà
- Đường kính lỗ khoan: 5mm
- Nối dây về Arduino: 4 core (R,G,B,GND)

Nút Smart Mode:
- Gắn cạnh bộ nút điều khiển cũ
- Đường kính lỗ khoan: 16mm  
- Nút có đèn LED tích hợp
- Dán nhãn: "SMART MODE"
```

## BƯỚC 3: ĐẤU NỐI ĐIỆN

### 3.1 Chuẩn bị hộp điều khiển
```bash
1. Hộp nhựa IP65 kích thước 150x100x75mm
2. Khoan lỗ cho:
   - Nguồn 5V DC
   - Dây từ cảm biến mưa  
   - Dây tới relay
   - Dây tới LED và nút bấm
   - Dây monitor từ hệ thống cũ

3. Lắp Arduino Nano vào breadboard mini
4. Lắp relay module 4 kênh
5. Đấu nối theo sơ đồ
```

### 3.2 Kết nối với hệ thống cũ
```bash
🚨 NGẮT NGUỒN HỆ THỐNG BẠT TRƯỚC KHI ĐẤU NỐI

Bước 1: Tìm dây tín hiệu 3 nút cũ
- Dùng multimeter đo điện áp
- Thường là 12V hoặc 24V DC
- Xác định dây (+) và (-)

Bước 2: Đấu song song relay với nút cũ
- Relay NO contact đấu song song với nút
- Common relay nối với (-) hệ thống
- Arduino chỉ điều khiển relay, không chạm điện áp cao

Bước 3: Monitor tín hiệu từ nút cũ
- Dùng optocoupler hoặc voltage divider
- Đưa tín hiệu về 5V cho Arduino
- Kết nối với D12, D13
```

## BƯỚC 4: LẬP TRÌNH VÀ TEST

### 4.1 Upload code lên Arduino
```bash
1. Kết nối Arduino với máy tính
2. Mở Arduino IDE
3. Chọn board: Arduino Nano
4. Chọn port COM
5. Upload code smart_awning_controller.ino
6. Mở Serial Monitor để debug
```

### 4.2 Test từng chức năng
```bash
Test 1: LED và nút bấm
- Nhấn nút Smart Mode
- Kiểm tra LED đổi màu
- Serial Monitor hiển thị trạng thái

Test 2: Cảm biến mưa  
- Nhỏ nước lên cảm biến
- Kiểm tra Serial Monitor hiển thị "RAINING"
- LED xanh dương nhấp nháy

Test 3: Limit switches
- Nhấn tay từng switch
- Serial Monitor hiển thị vị trí bạt
- Test cả 2 switch

Test 4: Relay (chưa kết nối hệ thống thật)
- Bật chế độ Smart Mode
- Nhỏ nước → relay KÉO kích hoạt
- Lau khô → relay THU kích hoạt
```

### 4.3 Test tích hợp với hệ thống thật
```bash
🚨 CẨN THẬN - TEST TỪNG BƯỚC

Bước 1: Test 1 relay  
- Kết nối chỉ relay STOP với hệ thống
- Nhấn nút Smart Mode
- Quan sát có tín hiệu STOP không

Bước 2: Test relay KÉO
- Đảm bảo bạt ở vị trí THU
- Test relay KÉO
- Sẵn sàng nhấn nút STOP thủ công

Bước 3: Test relay THU
- Đảm bảo bạt ở vị trí KÉO  
- Test relay THU
- Sẵn sàng nhấn nút STOP thủ công

Bước 4: Test hoàn chỉnh
- Bật chế độ Smart Mode
- Phun nước lên cảm biến → bạt tự kéo
- Lau cảm biến → bạt tự thu
```

## BƯỚC 5: TINH CHỈNH VÀ TỐI ƯU HÓA

### 5.1 Điều chỉnh ngưỡng cảm biến
```cpp
// Trong code Arduino
const int RAIN_THRESHOLD = 300; // Thay đổi giá trị này

// Test thực tế:
// - Mưa phùn: 400-500
// - Mưa vừa: 200-300  
// - Mưa to: 100-200
```

### 5.2 Điều chỉnh thời gian
```cpp
// Timeout các thao tác
const unsigned long OPERATION_TIMEOUT = 45000; // 45s

// Thời gian delay sau khi hết mưa
const unsigned long RAIN_STOP_DELAY = 300000; // 5 phút
```

### 5.3 Thêm tính năng nâng cao
```cpp
// Có thể thêm vào code:
- Cảm biến gió → thu bạt khi gió lớn
- Timer → tự thu bạt vào ban đêm  
- WiFi module → điều khiển từ xa
- Cảm biến ánh sáng → tự kéo khi nắng gắt
```

## BƯỚC 6: BẢO TRÌ VÀ TROUBLESHOOTING

### 6.1 Bảo trì định kỳ
```bash
Hàng tháng:
- [ ] Vệ sinh cảm biến mưa
- [ ] Kiểm tra kết nối dây điện
- [ ] Test limit switches
- [ ] Kiểm tra hộp chống nước

Hàng quý:
- [ ] Bôi trơn limit switches
- [ ] Kiểm tra relay hoạt động
- [ ] Update firmware nếu có
- [ ] Backup cài đặt
```

### 6.2 Xử lý sự cố
```bash
Sự cố 1: Bạt không tự kéo khi mưa
→ Kiểm tra cảm biến mưa
→ Kiểm tra chế độ Smart Mode có ON?
→ Kiểm tra limit switch vị trí THU

Sự cố 2: Bạt không dừng đúng vị trí
→ Kiểm tra limit switches
→ Điều chỉnh vị trí switch
→ Kiểm tra timeout trong code

Sự cố 3: Hệ thống không phản hồi
→ Kiểm tra nguồn 5V
→ Reset Arduino
→ Kiểm tra Serial Monitor

Sự cố 4: User override không hoạt động
→ Kiểm tra monitor pins D12, D13
→ Kiểm tra voltage divider
→ Test nút bấm cũ
```

## 💡 MẸO VÀ LƯU Ý QUAN TRỌNG

1. **Luôn có công tắc khẩn cấp** để ngắt toàn bộ hệ thống
2. **Test kỹ limit switches** - đây là phần dễ hỏng nhất  
3. **Backup code** và cài đặt trước khi chỉnh sửa
4. **Dùng optocoupler** nếu hệ thống cũ dùng điện áp cao
5. **Seal kỹ tất cả kết nối** để chống nước
6. **Ghi chú rõ ràng** tất cả dây nối
7. **Test trong thời tiết thật** chứ không chỉ test bằng nước