# SƠ ĐỒ ĐẤU DÂY HỆ THỐNG BẠT XẾP THÔNG MINH (DEMO MODEL)

## 1. TỔNG QUAN HỆ THỐNG

```
⚡ DEMO MODEL - CHỈ DÙNG 5V (MÔ HÌNH NHỎ)

Adapter 5V/3-5A ─┬── Arduino Nano (5V Logic)
                 │
                 └── L298N ─── Motor DC 5V (giảm tốc 1:48)
                      │
Arduino Nano ── Control Center ── 4 Button Interface
     │                               │
     ├── Motor Driver L298N          ├── EXTEND Button + LED
     ├── Rain Sensor                 ├── RETRACT Button + LED  
     ├── 2x Limit Switches           ├── STOP Button + LED
     └── Status LEDs                 └── SMART Button + LED
     
💡 NGUỒN: Chỉ cần 1 adapter 5V/3-5A cho toàn bộ hệ thống!
```

## 2. ARDUINO NANO - CHÂN KẾT NỐI CHI TIẾT

### Input Pins (Digital):
```
CHÂN    THIẾT BỊ                    MÔ TẢ                          KẾT NỐI
=================================================================================
D6      BTN_EXTEND                  Nút KÉO bạt                   Button → GND
D7      BTN_RETRACT                 Nút THU bạt                   Button → GND
D8      BTN_STOP                    Nút DỪNG                      Button → GND
D9      BTN_SMART_MODE              Nút chế độ thông minh         Button → GND
D10     LIMIT_EXTENDED              Limit switch vị trí kéo hết   Switch → GND
D11     LIMIT_RETRACTED             Limit switch vị trí thu hết   Switch → GND
D12     RAIN_SENSOR_DIGITAL         Cảm biến mưa (digital)        Sensor DO → Arduino
```

### Output Pins (Motor Control):
```
CHÂN    THIẾT BỊ                    MÔ TẢ                          KẾT NỐI  
=================================================================================
D2      MOTOR_ENABLE                PWM tốc độ motor              L298N EN → D2
D3      MOTOR_IN1                   Hướng motor 1                 L298N IN1 → D3
D4      MOTOR_IN2                   Hướng motor 2                 L298N IN2 → D4
D5      MOTOR_POWER_RELAY           Relay nguồn motor chính       Relay IN → D5
```

### Output Pins (LED Indicators):
```
CHÂN    THIẾT BỊ                    MÔ TẢ                          KẾT NỐI
=================================================================================
D13     LED_EXTEND                  LED nút KÉO                   LED + 220Ω → D13
A1      LED_RETRACT                 LED nút THU                   LED + 220Ω → A1
A2      LED_STOP                    LED nút STOP                  LED + 220Ω → A2
A3      LED_SMART_MODE              LED nút SMART                 LED + 220Ω → A3
A4      LED_STATUS_RED              LED trạng thái đỏ             LED + 220Ω → A4
A5      LED_STATUS_GREEN            LED trạng thái xanh           LED + 220Ω → A5
```

### Analog Pins:
```
CHÂN    THIẾT BỊ                    MÔ TẢ                          KẾT NỐI
=================================================================================
A0      RAIN_SENSOR_ANALOG          Cảm biến mưa (analog)         Sensor AO → A0
```

## 3. MẠCH ĐIỀU KHIỂN MOTOR L298N (ĐIỀU KHIỂN 2 CHIỀU)

### Sơ đồ kết nối:
```
L298N MODULE        ARDUINO NANO        MOTOR 5V            NGUỒN
=======================================================================
VCC                 -                   -                   5V+ (Adapter)
GND                 GND                 -                   GND
IN1                 D3                  -                   -
IN2                 D4                  -                   -
EN A                D2 (PWM)            -                   -
OUT1                -                   Motor Wire 1        -
OUT2                -                   Motor Wire 2        -
```

### Nguyên lý hoạt động 2 chiều:
**L298N H-Bridge tự động đảo cực motor** để điều khiển 2 chiều:

```
TRẠNG THÁI          IN1     IN2     EN      KẾT QUẢ              CHIỀU QUAY
=============================================================================
Dừng               LOW     LOW     LOW     Motor dừng           -
Kéo bạt (xuôi)     HIGH    LOW     PWM     OUT1=+5V, OUT2=GND   Xuôi chiều kim đồng hồ
Thu bạt (ngược)    LOW     HIGH    PWM     OUT1=GND, OUT2=+5V   Ngược chiều kim đồng hồ
Phanh              HIGH    HIGH    HIGH    Motor phanh          -
```

### Cách L298N tạo chuyển động 2 chiều:
```
▶ Kéo bạt (IN1=HIGH, IN2=LOW):
   Arduino D3 ─→ IN1 ┐
                      ├─→ H-Bridge ─→ OUT1(+5V) ─→ Motor(+) ─→ OUT2(GND)
   Arduino D4 ─→ IN2 ┘              Dòng điện: OUT1 → Motor → OUT2
                                     Motor quay xuôi

▶ Thu bạt (IN1=LOW, IN2=HIGH):
   Arduino D3 ─→ IN1 ┐
                      ├─→ H-Bridge ─→ OUT1(GND) ─→ Motor(-) ─→ OUT2(+5V)
   Arduino D4 ─→ IN2 ┘              Dòng điện: OUT2 → Motor → OUT1
                                     Motor quay ngược (đảo cực tự động)
```

### Hướng dẫn lắp đặt motor 5V:
1. **Kết nối motor với L298N:**
   - Nối 2 dây motor vào OUT1 và OUT2 (không cần phân biệt cực)
   - Nếu chiều quay ngược với mong muốn → đổi dây motor

2. **Cấp nguồn 5V:**
   - Adapter 5V/3-5A nối vào VCC và GND của L298N
   - Nối GND chung với Arduino
   - **Lưu ý**: Dùng chung 1 nguồn 5V cho cả Arduino và L298N

3. **Nối Arduino:**
   - D2 (PWM) → EN A (điều khiển tốc độ)
   - D3 → IN1 (điều khiển chiều 1)
   - D4 → IN2 (điều khiển chiều 2)

4. **Lắp motor vào khung (mô hình nhỏ):**
   - Motor giảm tốc TT 1:48 hoặc 1:90 (đã có hộp số)
   - Nối trực tiếp trục motor với trục bạt nhỏ
   - Hoặc dùng nhông/xích mini với tỷ lệ 1:2

## 4. MẠCH BUTTON VÀ LED

### Nút bấm 4 nút:
```
[VCC 5V] ──┬── [Button EXTEND] ──┬── [Pull-up 10kΩ] ── [D6]
           ├── [Button RETRACT] ─┼── [Pull-up 10kΩ] ── [D7]  
           ├── [Button STOP] ────┼── [Pull-up 10kΩ] ── [D8]
           └── [Button SMART] ───┴── [Pull-up 10kΩ] ── [D9]
                    │
                   GND
```

### LED indicator cho nút:
```
Arduino ──[220Ω]── LED ── GND

D13 ──[220Ω]── LED_EXTEND ── GND
A1  ──[220Ω]── LED_RETRACT ── GND
A2  ──[220Ω]── LED_STOP ── GND
A3  ──[220Ω]── LED_SMART ── GND
```

### LED trạng thái hệ thống:
```
A4 ──[220Ω]── LED_RED ── GND     (Chế độ Manual)
A5 ──[220Ω]── LED_GREEN ── GND   (Chế độ Auto)
```

## 5. CẢM BIẾN MƯA

```
RAIN SENSOR MODULE      ARDUINO NANO        NGUỒN
====================================================
VCC                     -                   3.3V/5V
GND                     GND                 GND  
DO (Digital Out)        D12                 -
AO (Analog Out)         A0                  -
```

**Vị trí lắp đặt cảm biến:**
- Module điều khiển: Trong hộp chống nước
- Sensor pad: Ngoài trời, có thể tiếp xúc mưa
- Khoảng cách: Tối đa 5m với cable chống nước

## 6. LIMIT SWITCHES

```
LIMIT SWITCH 1 (Extended Position):
[VCC] ── [10kΩ Pull-up] ── [D10] ── [Switch NO] ── [GND]

LIMIT SWITCH 2 (Retracted Position):  
[VCC] ── [10kΩ Pull-up] ── [D11] ── [Switch NO] ── [GND]
```

**Vị trí lắp đặt:**
- Switch 1: Vị trí bạt kéo hết (đầu ray)
- Switch 2: Vị trí bạt thu hết (gần motor)
- Loại switch: Micro switch có lever, IP65

## 7. NGUỒN CUNG CẤP (MÔ HÌNH DEMO - MOTOR 5V)

### Mạch nguồn đơn giản:
```
                    ┌── Arduino Nano (USB hoặc VIN)
                    │
Adapter 5V/3-5A ────┼── L298N VCC
                    │
                    └── Sensors + LEDs + Buttons
                    
GND chung: Adapter GND ─── Arduino GND ─── L298N GND
```

### Phân bổ công suất:
```
THIẾT BỊ                ĐIỆN ÁP    DÒNG ĐIỆN    CÔNG SUẤT
===============================================================
Motor DC 5V giảm tốc    5V         1-2A         5-10W
Arduino Nano            5V         50mA         0.25W
L298N Module (logic)    5V         30mA         0.15W
Rain Sensor             5V         20mA         0.1W
LEDs (6 cái)            5V         120mA        0.6W
Buttons + Pull-ups      5V         10mA         0.05W

TỔNG TIÊU THỤ                      1.2-2.2A     6-11W
NGUỒN KHUYẾN NGHỊ       5V         3-5A         15-25W (Adapter 5V/3-5A)
```

## 8. HỘP ĐIỀU KHIỂN VÀ LAYOUT

### Kích thước hộp điều khiển:
```
Hộp chính: 300x200x150mm (IP65)
├── Arduino Nano on breadboard
├── L298N Motor Driver  
├── Buck converter 12V→5V
├── Terminal blocks
├── Fuses & CB
└── Cooling fan (optional)

Hộp giao diện: 200x150x75mm (IP54)
├── 4x Button 22mm có LED
├── 2x LED status 
├── Emergency stop (optional)
└── Cable gland
```

## 9. BẢNG KIỂM TRA KẾT NỐI

### Trước khi cấp nguồn:
- [ ] Kiểm tra phân cực nguồn 12V
- [ ] Đo điện trở cách ly motor vs Arduino
- [ ] Kiểm tra pull-up resistors
- [ ] Test continuity tất cả dây nối
- [ ] Kiểm tra chống nước tất cả connector

### Sau khi cấp nguồn:
- [ ] Arduino boot thành công (LED on-board)
- [ ] Đo 5V tại chân VCC Arduino
- [ ] Test từng button → Serial Monitor
- [ ] Test rain sensor → Serial Monitor  
- [ ] Test limit switches → Serial Monitor
- [ ] Test motor (không tải) từng hướng
- [ ] Test motor với tải thật

## 10. LƯU Ý AN TOÀN (DEMO MODEL)

### Điện:
⚠️ **USB 5V** an toàn tuyệt đối
⚠️ **12V adapter** - không nguy hiểm nhưng cần chú ý:
   - Kiểm tra phân cực (+/-) trước khi kết nối
   - Không chạm ngắn mạch +12V và GND
⚠️ **GND chung** cho tất cả thiết bị (USB GND + 12V GND)
⚠️ **Fuse 3A** để bảo vệ motor (optional nhưng nên có)

### Cơ khí:
⚠️ **Limit switches** phải đáng tin cậy 100%
⚠️ **Motor mounting** chắc chắn, không rung
⚠️ **Cable management** tránh bị kẹt bởi bạt
⚠️ **Demo model**: Dùng motor nhỏ, tải trọng nhẹ

### Software:
⚠️ **Timeout protection** cho motor
⚠️ **Debounce** cho tất cả inputs
⚠️ **Serial monitoring** để debug
⚠️ **Backup code** trước khi chỉnh sửa

## 11. TROUBLESHOOTING

### Motor không chạy:
1. Kiểm tra nguồn 12V
2. Kiểm tra L298N connections
3. Kiểm tra PWM signal từ Arduino
4. Test motor trực tiếp với 12V

### Button không hoạt động:
1. Kiểm tra pull-up resistors
2. Test button với multimeter
3. Kiểm tra debounce trong code
4. Kiểm tra Serial Monitor output

### Limit switches không chính xác:
1. Điều chỉnh vị trí switch
2. Test mechanical operation
3. Kiểm tra wiring
4. Thay switch nếu cần

### Rain sensor không nhạy:
1. Vệ sinh sensor pad
2. Điều chỉnh threshold trong code
3. Kiểm tra analog reading
4. Test với nước thật