# HƯỚNG DẪN LẮP ĐẶT HỆ THỐNG BẠT XẾP THÔNG MINH HOÀN CHỈNH

## GIAI ĐOẠN 1: CHUẨN BỊ VÀ THIẾT KẾ (1-2 ngày)

### Bước 1.1: Khảo sát vị trí lắp đặt
```bash
📋 CHECKLIST KHẢO SÁT:
□ Đo kích thước bạt và hành trình cần thiết
□ Xác định vị trí motor và hướng quay
□ Chọn vị trí hộp điều khiển (gần điện, tránh ẩm)
□ Xác định đường kéo cable 
□ Chọn vị trí cảm biến mưa (không bị che chắn)
□ Kiểm tra nguồn điện 220V có sẵn
□ Đo khoảng cách từ motor đến điều khiển
```

### Bước 1.2: Mua sắm linh kiện
```bash
🛒 SHOPPING LIST HOÀN CHỈNH:

MOTOR & CONTROL:
□ Motor DC 12V 30-50W (có encoder tốt hơn)
□ L298N Motor Driver Module  
□ Arduino Nano + USB cable
□ Nguồn 12V/5A (outdoor rated)
□ Buck converter 12V→5V/2A

BUTTONS & INTERFACE:
□ Nút bấm có LED 22mm x4 (IP65)
□ LED 5mm đỏ/xanh x2
□ Điện trở 220Ω x6, 10kΩ x6

SENSORS:
□ Rain sensor module + pad
□ Limit switch IP65 x2
□ Cable sensor chống nước 5m

PROTECTION:
□ CB 10A x1, Fuse 5A x2
□ Contactor 25A/12VDC x1
□ Relay module 8 kênh

HOUSING & CABLE:
□ Hộp điều khiển 300x200x150mm IP65
□ Hộp button 200x150x75mm IP54  
□ Cable 4x1.5mm² x20m (motor)
□ Cable tín hiệu 10 core x10m
□ Ống luồn dây + phụ kiện

TOOLS:
□ Khoan + mũi khoan inox
□ Multimeter, test pen
□ Tang crimping, ống co nhiệt
□ Silicon chống nước
```

## GIAI ĐOẠN 2: CHẾ TẠO HỘP ĐIỀU KHIỂN (1 ngày)

### Bước 2.1: Chuẩn bị hộp điều khiển chính
```bash
1. LAYOUT TRONG HỘP:
   ┌─────────────────────────────────────┐
   │ [CB 10A]  [Nguồn 12V]  [Buck 5V]   │
   │                                     │
   │ [Arduino]  [L298N]  [Relay Module]  │
   │                                     │
   │ [Terminal Blocks]  [Fuses]          │
   └─────────────────────────────────────┘

2. KHOAN LỖ:
   - Top: 4x lỗ M6 cho cable gland
   - Front: 1x lỗ 22mm cho emergency stop
   - Side: Cooling vent (optional)

3. MOUNTING:
   - Arduino: Standoffs M3 x4
   - L298N: Screws M3 x4  
   - Nguồn: Bracket + screws
   - Heat sink cho L298N nếu cần
```

### Bước 2.2: Đấu dây trong hộp điều khiển
```bash
🔌 THỨ TỰ ĐẤU DÂY:

1. NGUỒN CHÍNH:
   220V ─── [CB 10A] ─── [Biến áp 12V/5A] ─── [+12V Bus]
                                               │
                                               ├── L298N VCC
                                               ├── Motor via Contactor
                                               └── Buck 5V input

2. NGUỒN 5V:
   Buck 5V ─── [+5V Bus] ─── Arduino VIN
                         └── Sensors VCC

3. GND CHUNG:
   Tất cả GND nối chung tại 1 terminal block

4. SIGNAL WIRES:
   Arduino ↔ L298N (D2,D3,D4,D5)
   Arduino ↔ Sensors (D6-D12, A0)
   Arduino ↔ LEDs (D13, A1-A5)
```

## GIAI ĐOẠN 3: CHẾ TẠO HỘP GIAO DIỆN (0.5 ngày)

### Bước 3.1: Layout hộp button
```bash
HỘP BUTTON LAYOUT (view từ phía trước):

┌─────────────────────────────────┐
│  [STATUS]     [STATUS]          │ ← LEDs trạng thái
│   RED 💡      GREEN 💡         │
│                                 │
│  ┌─────┐ ┌─────┐ ┌─────┐        │
│  │ KÉO │ │ THU │ │STOP │        │ ← Buttons chính  
│  │ 💡  │ │ 💡  │ │ 💡  │        │
│  └─────┘ └─────┘ └─────┘        │
│                                 │
│         ┌─────────┐              │
│         │ SMART   │              │ ← Smart mode toggle
│         │ MODE 💡 │              │
│         └─────────┘              │
└─────────────────────────────────┘
```

### Bước 3.2: Đấu nối buttons
```bash
MỖI BUTTON KẾT NỐI:
- 1 chân: 5V (chung)
- 1 chân: GND (chung)  
- 1 chân: Signal → Arduino digital pin
- 2 chân LED: 5V qua 220Ω → Arduino output pin
```

## GIAI ĐOẠN 4: LẮP ĐẶT MOTOR VÀ CƠ KHÍ (1 ngày)

### Bước 4.1: Lắp đặt motor
```bash
1. MOTOR MOUNTING:
   - Chọn motor DC 12V có moment đủ lớn
   - Gắn chắc chắn vào khung bạt
   - Đảm bảo trục motor thẳng hàng
   - Có thể cần hộp số giảm tốc

2. CƠ CẤU TRUYỀN ĐỘNG:
   Option A: Trực tiếp (motor → drum)
   Option B: Dây đai (motor → pulley → drum)  
   Option C: Xích (motor → sprocket → drum)

3. LIMIT SWITCHES:
   - Switch 1: Gắn ở vị trí bạt kéo hết
   - Switch 2: Gắn ở vị trí bạt thu hết  
   - Dùng cần gạt hoặc cam để kích hoạt
   - Đấu dây về hộp điều khiển
```

### Bước 4.2: Test cơ khí
```bash
TEST KHÔNG TẢI:
□ Motor quay 2 chiều mượt mà
□ Không có tiếng kêu bất thường
□ Limit switches kích hoạt đúng vị trí
□ Không có điểm kẹt trong hành trình

TEST CÓ TẢI:
□ Motor đủ lực để kéo bạt
□ Tốc độ hợp lý (không quá nhanh/chậm)
□ Dừng chính xác tại limit switches
□ Không quá tải motor
```

## GIAI ĐOẠN 5: LẮP ĐẶT CẢM BIẾN (0.5 ngày)

### Bước 5.1: Cảm biến mưa
```bash
VỊ TRÍ LÝ TƯỞNG:
- Cao hơn bạt 50cm trở lên
- Không bị che chắn bởi mái, cây
- Khoảng cách đến điều khiển < 10m
- Dễ vệ sinh và bảo trì

CÁCH LẮP:
1. Khoan lỗ 6mm, cắm nở M6
2. Gắn bracket bằng inox
3. Module sensor trong hộp nhỏ IP65
4. Sensor pad phơi ngoài trời
5. Cable 4 core chống nước về điều khiển
6. Seal tất cả kết nối bằng silicon
```

### Bước 5.2: Test cảm biến
```bash
TEST CẢM BIẾN MƯA:
□ Đọc giá trị analog khi khô: ~1020
□ Nhỏ nước → giá trị analog giảm < 400
□ Digital output chuyển từ HIGH → LOW
□ Serial Monitor hiển thị thông tin chính xác
□ Lau khô → trở về trạng thái ban đầu
```

## GIAI ĐOẠN 6: LẬP TRÌNH VÀ TEST (1 ngày)

### Bước 6.1: Upload code và test từng phần
```bash
1. UPLOAD CODE:
   - Connect Arduino qua USB
   - Upload smart_awning_controller.ino
   - Mở Serial Monitor 9600 baud

2. TEST INPUT:
   - Nhấn từng button → check Serial Monitor
   - Test rain sensor → phun nước
   - Test limit switches → nhấn tay

3. TEST OUTPUT:  
   - Check LEDs sáng theo đúng trạng thái
   - Test motor 2 chiều (không tải)
   - Verify motor stops at limits
```

### Bước 6.2: Integration test
```bash
TEST TÍCH HỢP:
□ Manual mode: Button KÉO → motor extend
□ Manual mode: Button THU → motor retract  
□ Manual mode: Button STOP → motor stops
□ Smart mode: Rain → auto extend
□ Smart mode: No rain → auto retract
□ Override: Manual button disables smart mode
□ Emergency: Limit switches stop motor
□ Timeout: Motor auto-stop after 60s
```

## GIAI ĐOẠN 7: TINH CHỈNH VÀ TỐI ƯU HÓA (0.5 ngày)

### Bước 7.1: Calibration
```bash
ĐIỀU CHỈNH TRONG CODE:

1. Rain Threshold:
   const int RAIN_THRESHOLD = 400; // Tăng = nhạy hơn

2. Motor Speed:  
   const int MOTOR_SPEED = 200; // 0-255, giảm = chậm hơn

3. Timeouts:
   const unsigned long MOTOR_MAX_RUNTIME = 45000; // 45s

4. Debounce:
   const unsigned long DEBOUNCE_TIME = 200; // 200ms
```

### Bước 7.2: Safety test
```bash
TEST AN TOÀN:
□ CB 10A trip khi motor quá tải  
□ Emergency stop ngắt ngay lập tức
□ Limit switches không bao giờ fail
□ Motor timeout hoạt động
□ Không có short circuit
□ Tất cả kết nối chắc chắn
```

## GIAI ĐOẠN 8: VẬN HÀNH THỬ NGHIỆM (2-3 ngày)

### Bước 8.1: Test thời tiết thật
```bash
TEST TRONG ĐIỀU KIỆN THẬT:
□ Test khi mưa phùn nhẹ
□ Test khi mưa to, gió lớn
□ Test nhiều lần trong ngày
□ Check độ ổn định sau 24h
□ Monitor Serial log để debug
```

### Bước 8.2: User training
```bash
HƯỚNG DẪN SỬ DỤNG:
1. Các chế độ hoạt động
2. Cách bật/tắt smart mode
3. Cách dừng khẩn cấp
4. Vệ sinh cảm biến mưa
5. Khi nào cần bảo trì
6. Troubleshooting cơ bản
```

## 💡 MẸO QUAN TRỌNG:

### Về điện:
✅ **Luôn test với multimeter** trước khi cấp nguồn
✅ **Double-check phân cực** của tất cả kết nối DC
✅ **Dùng terminal blocks** thay vì nối dây trực tiếp
✅ **Label tất cả dây** để dễ troubleshoot

### Về cơ khí:
✅ **Motor phải có moment dự trữ** ít nhất 2x yêu cầu
✅ **Limit switches là điểm quan trọng nhất** - test kỹ
✅ **Bearing và guide** phải mượt để giảm tải cho motor
✅ **Weather protection** cho tất cả outdoor components

### Về software:
✅ **Serial Monitor** là công cụ debug tốt nhất
✅ **Backup code** trước khi thay đổi
✅ **Test edge cases**: mất điện, button stuck, etc.
✅ **Comment code** rõ ràng để maintain sau này

## 🚨 EMERGENCY PROCEDURES:

### Khi motor không dừng:
1. Nhấn nút STOP ngay lập tức
2. Tắt CB 10A nếu STOP không hoạt động  
3. Rút dây nguồn 220V
4. Check code và wiring

### Khi hệ thống hoạt động sai:
1. Chuyển về manual mode
2. Kiểm tra Serial Monitor
3. Test từng component riêng biệt
4. Restore backup code nếu cần

### Khi mưa to + gió lớn:
1. Hệ thống sẽ tự thu bạt (nếu safe)
2. Có thể manual override về vị trí an toàn
3. Tắt smart mode trong thời tiết xấu
4. Kiểm tra sau khi thời tiết ổn định

**⚠️ LƯU Ý: Đây là dự án DIY phức tạp, cần kinh nghiệm về điện và lập trình. Nếu không chắc chắn, nên nhờ thợ điện có kinh nghiệm hỗ trợ phần 220V và motor.**