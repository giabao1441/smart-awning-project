# HƯỚNG DẪN LẮP ĐẶT HỆ THỐNG BẠT XẾP THÔNG MINH HOÀN CHỈNH

## GIAI ĐOẠN 1: CHUẨN BỊ VÀ THIẾT KẾ (1-2 ngày)

### Bước 1.1: Khảo sát mô hình demo
```bash
📋 CHECKLIST CHO MÔ HÌNH DEMO NHỎ:
□ Kích thước mô hình: ~30x40cm (hoặc tùy chỉnh)
□ Loại bạt: Vải mỏng, nhựa mềm (nhẹ ~50-200g)
□ Vị trí motor: Một đầu khung
□ Breadboard: Đặt cạnh motor hoặc riêng biệt
□ Nguồn điện: Adapter 5V/3-5A (cắm điện 220V thường)
□ Cảm biến mưa: Đặt ngoài trời hoặc test bằng nước
□ Limit switches: 2 đầu hành trình bạt
```

### Bước 1.2: Mua sắm linh kiện
```bash
🛒 SHOPPING LIST HOÀN CHỈNH:

MOTOR & CONTROL (cho mô hình demo nhỏ):
□ Motor DC 5V giảm tốc TT 1:48 hoặc 1:90 (~80-150k)
□ L298N Motor Driver Module (~80k)
□ Arduino Nano + USB cable (~150k)
□ Adapter 5V/3-5A (~150k) - nguồn duy nhất cho toàn bộ hệ thống

BUTTONS & INTERFACE:
□ Nút bấm mini x4 (12mm hoặc breadboard buttons) (~50k)
□ LED 5mm đỏ/xanh x6 (~30k)
□ Điện trở 220Ω x6, 10kΩ x6 (~20k)

SENSORS:
□ Rain sensor module FC-37 (~50k)
□ Limit switch mini (NO) x2 (~40k)
□ Cable jumper wire (~50k)

ASSEMBLY (mô hình demo):
□ Breadboard 830 holes (~50k)
□ Khung nhôm/nhựa 30x40cm (~100k)
□ Dây jumper breadboard male-male/female-female (~30k)
□ Ốc vít M3 + đai ốc (~20k)
□ Vải/nhựa mỏng làm bạt (~30k)
□ Trục nhựa/gỗ 8mm cho bạt (~20k)

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

### Bước 2.2: Đấu dây trong hộp điều khiển (Demo)
```bash
🔌 THỨ TỰ ĐẤU DÂY:

1. NGUỒN ARDUINO:
   USB 5V ─── Arduino Nano USB port
   
2. NGUỒN MOTOR:
   12V Adapter (+) ─── L298N VCC
   12V Adapter (-) ─── L298N GND ─── Arduino GND (GND chung!)

3. SIGNAL WIRES:
   Arduino ↔ L298N (D2,D3,D4,D5)
   Arduino ↔ Sensors (D6-D12, A0)
   Arduino ↔ LEDs (D13, A1-A5)
   
4. LƯU Ý:
   - GND của USB và 12V PHẢI nối chung
   - Kiểm tra phân cực 12V trước khi bật
   - Dùng breadboard để dễ kết nối
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

### Bước 4.1: Lắp đặt motor 2 chiều
```bash
1. CHỌN MOTOR PHÙ HỢP:
   ✅ Motor DC 12V có 2 dây (không phân cực +/-)
   ✅ Công suất: 10-30W (demo) hoặc 30-50W (thực tế)
   ✅ Có hộp số giảm tốc (tăng mô-men xoắn)
   ✅ Loại motor khuyến nghị:
      - DC gear motor 12V 100-200 RPM
      - Worm gear motor (tự hãm)
      - Motor với encoder (optional)

2. KẾT NỐI MOTOR VỚI L298N (ĐIỀU KHIỂN 2 CHIỀU):
   
   Motor DC 12V (2 dây bất kỳ)
   ┌────────┐
   │ Wire 1 │───────────┐
   └────────┘           │
   ┌────────┐           ↓
   │ Wire 2 │───────┐   ┌─────────────────┐
   └────────┘       └───│ L298N OUT1      │
                        │       OUT2      │───→ Đảo chiều tự động
                        │                 │
   Arduino Nano         │ IN1 ← D3        │
   ┌──────────┐         │ IN2 ← D4        │
   │ D2 (PWM) │─────────│ EN  ← D2        │
   │ D3       │─────────│                 │
   │ D4       │─────────│ VCC ← 12V (+)   │
   │ GND      │─────────│ GND ← 12V (-)   │
   └──────────┘         └─────────────────┘
   
   ⚡ NGUYÊN LÝ H-BRIDGE (L298N):
   
   Chiều 1 (KÉO BẠT):
   IN1=HIGH, IN2=LOW  → OUT1=+12V, OUT2=GND
                      → Motor quay xuôi
   
   Chiều 2 (THU BẠT):
   IN1=LOW, IN2=HIGH  → OUT1=GND, OUT2=+12V
                      → Motor quay ngược
   
   DỪNG:
   IN1=LOW, IN2=LOW   → Motor dừng
   
3. LẮP ĐẶT CƠ KHÍ:

   A. MOTOR MOUNTING (Quan trọng!):
      ┌──────────────────────────────────┐
      │  [Motor] → [Khớp nối] → [Trục]  │
      │     ↓                      ↓      │
      │  [Gá đỡ]              [Ổ bi]    │
      └──────────────────────────────────┘
      
      - Gá motor CỐ ĐỊNH, không rung
      - Dùng đệm cao su giảm chấn
      - Khớp nối linh hoạt (coupling)
      - Đảm bảo đồng tâm với trục bạt

   B. CƠ CẤU TRUYỀN ĐỘNG:
   
   Option 1: TRỰC TIẾP (đơn giản nhất)
   ┌──────┐     ┌──────────┐
   │ Motor│─────│ Trục bạt │
   └──────┘     └──────────┘
   ✅ Ưu: Đơn giản, ít hỏng hóc
   ❌ Nhược: Cần motor công suất lớn
   
   Option 2: DÂY ĐAI (khuyến nghị cho demo)
   ┌──────┐     ╭─────╮     ┌──────────┐
   │ Motor│─────│Pulley│─────│ Trục bạt │
   └──────┘     ╰─────╯     └──────────┘
               Dây đai
   ✅ Ưu: Giảm tốc, tăng mô-men, êm
   ✅ Tỷ số truyền: 1:2 hoặc 1:3
   
   Option 3: XÍCH (bền nhất)
   ┌──────┐     ╔═════╗     ┌──────────┐
   │ Motor│─────║Xích ║─────│ Trục bạt │
   └──────┘     ╚═════╝     └──────────┘
   ✅ Ưu: Bền, chịu tải cao
   ❌ Nhược: Ồn, cần bôi trơn

4. LẮP ĐẶT CHI TIẾT:

   Bước 1: GẮN MOTOR
   - Vị trí: Sát trục cuộn bạt, trong nhà
   - Gá đỡ: Khung sắt hoặc gỗ chắc chắn
   - Lưu ý: Không để motor bị ướt

   Bước 2: NỐI TRỤC
   - Dùng khớp nối mềm (flexible coupling)
   - Hoặc dùng dây đai/xích với 2 bánh răng
   - Kiểm tra: Trục quay mượt, không kêu

   Bước 3: ĐẤU DÂY MOTOR
   - 2 dây motor nối với OUT1, OUT2 của L298N
   - KHÔNG CẦN PHÂN BIỆT +/-
   - Nếu motor quay ngược → đổi 2 dây

   Bước 4: TEST HƯỚNG QUAY
   ```cpp
   // Upload code test đơn giản
   digitalWrite(MOTOR_IN1, HIGH);
   digitalWrite(MOTOR_IN2, LOW);
   analogWrite(MOTOR_ENABLE, 150); // Tốc độ chậm
   delay(2000); // Chạy 2 giây
   
   // Quan sát:
   // - Nếu bạt KÉO ra → Đúng hướng
   // - Nếu bạt THU vào → Đổi dây OUT1 ↔ OUT2
   ```

5. ĐIỀU CHỈNH TỐC ĐỘ:
   ```cpp
   // Trong code Arduino
   const int MOTOR_SPEED = 200; // 0-255
   
   // Demo/Test: 100-150 (chậm, an toàn)
   // Thực tế: 200-255 (nhanh)
   ```

6. AN TOÀN:
   ⚠️ Test KHÔNG TẢI trước (không gắn bạt)
   ⚠️ Có nút STOP dễ tiếp cận
   ⚠️ Kiểm tra motor không quá nóng (>60°C)
   ⚠️ Limit switches PHẢI hoạt động 100%

7. LẮP ĐẶT LIMIT SWITCHES:
   
   Switch 1 (VỊ TRÍ KÉO HẾT):
   ┌─────────────────────────────┐
   │        Bạt kéo →            │
   │  ████████████████  [SW1]    │ ← Gắn ở đầu ray
   │                    ↑         │
   │              Cần gạt kích   │
   └─────────────────────────────┘
   
   Switch 2 (VỊ TRÍ THU HẾT):
   ┌─────────────────────────────┐
   │    [Motor] [SW2]            │ ← Gắn gần motor
   │        ↑                    │
   │   Cam kích hoạt             │
   │  ███  ← Bạt thu             │
   └─────────────────────────────┘
   
   Cách đấu:
   - Loại: Normally Open (NO)
   - Kết nối: Switch → GND khi nhấn
   - Pull-up: 10kΩ lên 5V (trong code)
   - Test: Nhấn tay → Serial Monitor hiển thị
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