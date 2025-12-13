# SƠ ĐỒ KẾT NỐI HỆ THỐNG BẠT XẾP THÔNG MINH

## 1. ARDUINO NANO - CHÂN KẾT NỐI

```
ARDUINO NANO         THIẾT BỊ                           MÔ TẢ
================================================================
D2                   Nút bấm có đèn (NO)               Kích hoạt chế độ thông minh
D3                   Limit Switch 1 (NO)               Phát hiện bạt kéo hết
D4                   Limit Switch 2 (NO)               Phát hiện bạt thu hết
D5                   Rain Sensor (Digital Out)         Tín hiệu digital cảm biến mưa
D6                   LED RGB - chân Red                 Báo chế độ Manual (đỏ)
D7                   LED RGB - chân Green               Báo chế độ Auto (xanh lá)
D8                   LED RGB - chân Blue                Báo đang hoạt động (xanh dương)
D9                   Relay Module - IN1                 Điều khiển tín hiệu KÉO bạt
D10                  Relay Module - IN2                 Điều khiển tín hiệu THU bạt  
D11                  Relay Module - IN3                 Điều khiển tín hiệu STOP
D12                  Hệ thống cũ - Nút KÉO              Monitor lệnh từ user
D13                  Hệ thống cũ - Nút THU              Monitor lệnh từ user
A0                   Rain Sensor (Analog Out)           Tín hiệu analog cảm biến mưa
5V                   VCC của tất cả module              Nguồn 5V
GND                  GND của tất cả module              Nguồn âm
```

## 2. KẾT NỐI RELAY MODULE VỚI HỆ THỐNG BẠT XẾP CŨ

```
RELAY MODULE         HỆ THỐNG BẠT XẾP CŨ                KẾT NỐI
================================================================
Relay 1 (NO)         Dây tín hiệu NÚT KÉO               Song song với nút KÉO
Relay 2 (NO)         Dây tín hiệu NÚT THU               Song song với nút THU  
Relay 3 (NO)         Dây tín hiệu NÚT STOP              Song song với nút STOP
Common               GND hệ thống điều khiển bạt        Chung mass
```

## 3. CẢM BIẾN MƯA - VỊ TRÍ LẮP ĐẶT

```
RAIN SENSOR          VỊ TRÍ                             LƯU Ý
================================================================
Module chính         Gần hộp điều khiển                 Trong hộp chống nước
Sensor pad           Vị trí có thể tiếp xúc mưa         Xa module 2-5m
                     - Mái hiên
                     - Ban công  
                     - Sân thượng
Dây nối              Cable 3 core (VCC,GND,Signal)      Dài 2-5m, chống nước
```

## 4. LIMIT SWITCH - VỊ TRÍ LẮP ĐẶT

```
LIMIT SWITCH         VỊ TRÍ                             CHỨC NĂNG
================================================================
Switch 1             Vị trí bạt KÉO HẾT                 Báo bạt đã mở hoàn toàn
                     - Gắn trên ray  
                     - Bánh xe đẩy kích hoạt
                     
Switch 2             Vị trí bạt THU HẾT                 Báo bạt đã thu hoàn toàn
                     - Gắn đầu motor
                     - Bánh xe/cần gạt kích hoạt
```

## 5. LED RGB - HIỂN THỊ TRẠNG THÁI

```
TRẠNG THÁI           MÀU LED                            Ý NGHĨA
================================================================
Manual Mode          Đỏ sáng                           Chế độ thủ công
Auto Mode            Xanh lá sáng                      Chế độ tự động
Đang hoạt động       Xanh dương nhấp nháy              Motor đang chạy
User Override        Đỏ nhấp nháy                      User đã can thiệp
Phát hiện mưa        Xanh dương + xanh lá              Mưa + auto mode
Khởi động            Đỏ-Xanh lá-Xanh dương             Hệ thống starting
```

## 6. NGUỒN ĐIỆN

```
THIẾT BỊ             ĐIỆN ÁP                           DÒNG ĐIỆN
================================================================
Arduino Nano         5V DC                             50mA
Relay Module         5V DC                             100mA
Rain Sensor          3.3-5V DC                         20mA
LED RGB              3.3V DC                           60mA (20mA/color)
Limit Switch         5V DC                             0mA (passive)
Nút bấm              5V DC                             0mA (passive)

TỔNG                 5V DC                             230mA
Khuyến nghị          5V/1A adapter                     Dự phòng 4x
```

## 7. SƠ ĐỒ ĐẤU DÂY

```
   [NGUỒN 5V/1A]
         |
    ┌────┴────┐
    │ ARDUINO │
    │  NANO   │
    └─────────┘
         │
    ┌────┴────┐
    │ RELAY   │    ════════════════════════════════════
    │ MODULE  │ ═══╣  ĐẤU SONG SONG VỚI HỆ THỐNG CŨ  ╠═══
    └─────────┘    ════════════════════════════════════
         │
    ┌────┴────┐
    │ SENSORS │
    │& BUTTONS│
    └─────────┘
```

## 8. BẢNG KIỂM TRA KẾT NỐI

□ Arduino Nano nhận nguồn 5V
□ Relay module kết nối với Arduino (D9,D10,D11)
□ Relay output đấu song song với nút bấm cũ
□ Cảm biến mưa kết nối D5 và A0
□ Limit switch kết nối D3 và D4  
□ LED RGB kết nối D6,D7,D8
□ Nút smart mode kết nối D2
□ Monitor nút cũ kết nối D12,D13
□ Tất cả GND nối chung
□ Test từng chức năng riêng biệt

## 9. LƯU Ý AN TOÀN

⚠️ Ngắt nguồn hệ thống bạt trước khi đấu nối
⚠️ Kiểm tra điện áp trước khi kết nối
⚠️ Sử dụng hộp chống nước cho Arduino
⚠️ Cảm biến mưa phải chống nước IP65+
⚠️ Test relay trước khi kết nối với hệ thống thật
⚠️ Có công tắc khẩn cấp để ngắt hệ thống