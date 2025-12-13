# 🏠 SMART AWNING SYSTEM - HỆ THỐNG BẠT XẾP THÔNG MINH

## 📋 Mô tả dự án

Hệ thống điều khiển bạt xếp tự động thông minh với khả năng:
- **Điều khiển motor DC** xuôi/ngược hoàn chỉnh
- **Giao diện 4 nút bấm**: KÉO/THU/STOP/SMART MODE  
- **Tự động theo thời tiết**: Phát hiện mưa và điều chỉnh bạt
- **An toàn cao**: Limit switches, timeout, emergency stop
- **Ưu tiên người dùng**: Lệnh thủ công luôn được ưu tiên

## 📁 Cấu trúc file

### Code chính:
- `smart_awning_controller.ino` - Code Arduino hoàn chỉnh

### Tài liệu thiết kế:
- `complete_awning_system_wiring.md` - Sơ đồ đấu dây chi tiết
- `complete_awning_installation_guide.md` - Hướng dẫn lắp đặt từng bước

### Tài liệu phiên bản cũ:
- `smart_awning_wiring_diagram.md` - Sơ đồ kết nối phiên bản đầu
- `smart_awning_installation_guide.md` - Hướng dẫn lắp đặt phiên bản đầu

## 🛠️ Thông số kỹ thuật

### Phần cứng chính:
- **Vi điều khiển**: Arduino Nano
- **Motor**: DC 5V 3-10W với L298N driver (cho mô hình demo nhỏ)
- **Nguồn**: Adapter 5V/3-5A (nguồn duy nhất cho toàn bộ hệ thống)
- **Giao diện**: 4 nút bấm có LED + 2 LED trạng thái
- **Cảm biến**: Rain sensor + 2x Limit switches

### Tính năng:
✅ Điều khiển motor 2 chiều với PWM  
✅ Tự động kéo bạt khi mưa  
✅ Tự động thu bạt khi hết mưa  
✅ Ưu tiên lệnh thủ công  
✅ Bảo vệ quá tải và timeout  
✅ LED báo trạng thái trực quan  

## 💰 Chi phí dự kiến (Mô hình Demo Nhỏ - Motor 5V)

**Tổng chi phí**: 1.2 - 1.8 triệu VNĐ

### Phân bổ chi phí:
- Motor 5V + L298N: ~200k
- Arduino Nano: ~150k
- Nguồn 5V/5A: ~150k
- Rain sensor + Limit switches: ~150k
- Buttons + LEDs: ~200k
- Breadboard + Dây nối: ~150k
- Khung + Phụ kiện: ~200k

## ⏱️ Thời gian thực hiện (Mô hình Demo)

**Tổng thời gian**: 2-3 ngày

### Lịch trình:
1. **Mua sắm + Chuẩn bị**: 0.5 ngày
2. **Chế tạo hộp điều khiển**: 0.5 ngày  
3. **Lập đặt motor + cơ khí**: 0.5 ngày
4. **Lập trình + test**: 0.5 ngày
5. **Tinh chỉnh + test thực tế**: 1 ngày

## 🚀 Hướng dẫn bắt đầu

### Bước 1: Đọc tài liệu
1. Đọc `complete_awning_system_wiring.md` để hiểu sơ đồ đấu dây
2. Đọc `complete_awning_installation_guide.md` để biết cách lắp đặt

### Bước 2: Mua linh kiện
- Xem danh sách chi tiết trong installation guide
- Tổng chi phí khoảng 3.8-4.5 triệu VNĐ

### Bước 3: Lập trình
- Upload `smart_awning_controller.ino` lên Arduino Nano
- Test từng chức năng qua Serial Monitor

### Bước 4: Lắp đặt
- Theo hướng dẫn từng bước trong installation guide
- Test kỹ trước khi vận hành chính thức

## ⚠️ Lưu ý an toàn (Mô hình Demo 5V)

### Điện:
- **Adapter 5V/3-5A** - an toàn, không nguy hiểm
- **GND chung** - Adapter, Arduino, L298N phải chung GND
- **Không ngắn mạch** +5V và GND khi motor chạy
- **Test riêng** từng module trước khi lắp ghép

### Cơ khí:
- **Limit switches** phải chắc chắn, test nhiều lần
- **Motor mounting** chắc, tránh rung lắc
- **Bạt nhẹ** - chỉ dùng vải mỏng ~50-200g cho motor 5V
- **Trục truyền động** - kiểm tra không bị kẹt

### Software:
- **Timeout protection** - motor tự dừng sau 60s
- **Debounce** - chống nhiễu nút bấm
- **Serial monitoring** để debug
- **Backup code** trước khi sửa

## 🔧 Troubleshooting

### Sự cố thường gặp:
1. **Motor không chạy** → Check nguồn 12V, L298N connections
2. **Button không hoạt động** → Check pull-up resistors, debounce
3. **Limit switches sai** → Adjust vị trí, check wiring  
4. **Rain sensor không nhạy** → Clean sensor pad, adjust threshold

### Debug tools:
- Serial Monitor 9600 baud để xem log
- Multimeter để check điện áp/dòng điện  
- Test từng component riêng biệt

## 📞 Hỗ trợ

Nếu gặp vấn đề trong quá trình thực hiện:
1. Kiểm tra Serial Monitor để debug
2. So sánh với sơ đồ đấu dây
3. Test từng component riêng lẻ
4. Backup và restore code nếu cần

## 🔮 Mở rộng tương lai

Có thể thêm các tính năng:
- **WiFi control** - Điều khiển từ xa qua smartphone
- **Weather API** - Dự báo thời tiết tự động
- **Wind sensor** - Thu bạt khi gió lớn  
- **Timer control** - Lập lịch tự động
- **Solar panel** - Nguồn điện tự cấp
- **Security cam** - Giám sát tự động

---

**⚠️ Disclaimer**: Đây là dự án DIY phức tạp. Nếu không có kinh nghiệm về điện và lập trình, nên nhờ thợ chuyên môn hỗ trợ phần 220V và motor.


🎯 Hệ thống hoàn chỉnh cần thiết kế:
    Mạch điều khiển motor (xuôi/ngược)
    Bộ điều khiển 3 nút bấm (KÉO/THU/STOP)
    Nút Smart Mode thứ 4 + LED báo trạng thái
    Cảm biến mưa + tự động hóa
    Limit switches an toàn
    Arduino làm bộ não trung tâm
🛠️ Danh sách linh kiện HOÀN CHỈNH:
Phần điều khiển motor:
    Motor DC 12V/24V x1 (800k-1.5tr) - Motor bạt xếp
    Driver motor L298N x1 (80k) - Điều khiển xuôi/ngược
    Nguồn 12V/5A x1 (200k) - Cấp điện cho motor
    Capacitor 1000µF/25V x2 (40k) - Lọc nguồn motor
Vi điều khiển & Control:
    Arduino Nano x1 (150k)
    Relay 8 kênh 5V x1 (120k) - Điều khiển motor + tín hiệu
    Module cảm biến mưa x1 (50k)
    Limit switch x2 (80k) - Đầu cuối hành trình
Giao diện người dùng:
    Nút bấm có đèn 22mm x3 (120k) - KÉO/THU/STOP
    Nút toggle có đèn 22mm x1 (50k) - Smart Mode
    LED RGB 5mm x1 (20k) - Báo trạng thái hệ thống
    Box điều khiển IP65 x1 (150k)
Phụ kiện & An toàn:
    CB bảo vệ 10A x1 (80k) - Cầu dao an toàn
    Contactor 25A/12V x1 (150k) - Bảo vệ motor
    Fuse 5A x3 (30k) - Cầu chì bảo vệ
    Biến áp 220V→12V/5A x1 (300k) - Nguồn chính
Dây & Kết nối:
    Cable 4x1.5mm² x10m (200k) - Dây motor
    Cable tín hiệu 8 core x5m (100k)
    Ống luồn dây + phụ kiện (150k)
💰 TỔNG CHI PHÍ Dự KIẾN: ~3.8-4.5 triệu VNĐ




===================================
            PROMPT
===================================
bạn rất chi tiết. Hhệ thống 3 nút bấm điều khiển hoạt động là chúng ta sẽ thiết kế luôn cho người dùng nhấm luôn. và chúng ta cần thiết kế lắp đặt để mô tơ chạy xuôi chạy ngược luôn. tôi sẽ nhắc lại prompt là nhờ bạn setup lại giúp tôi.

Bây giờ chúng ta chỉ tập trung việc sáng tạo DIY cho các thiét bị tự động thôi.
Bạt xếp đó đã có hệ thống điện điều khiển 3 nút để có thể điều khiển kéo, xếp bạt, stop tại vị trí mong muốn.
Bây giờ tôi muốn tự thiết kế hệ thống tự động thông minh cho bạt xếp:
- Hệ thống 3 nút bấm điều khiển hoạt động là chúng ta sẽ thiết kế luôn cho người dùng nhấm (kéo, xếp bạt, stop tại vị trí bát kỳ).
- Chúng ta sẽ có công tắt để kích hoạt (turn on/off) chế động thông minh cho bạt xếp (có thể thêm đèn led cảnh báo để biết trạng thái của chế độ) - nút này sẽ là nút hứ 4, nút độc lập với hệ thống 3 nút ở trên. 
- Khi trời mưa bạt xếp sẽ tự động kéo ra để che. Dĩ nhiên bạt đã được kéo rồi thì không cần kéo nữa.
- Trong quá thì kéo/thu được ra lệnh từ hệ thống, nếu có sự can thiệp từ con người ra lệnh cho bạt kéo thông qua hệ thống 3 nút bấm thì sẽ ưu tiên lệnh từ con người (có thể chuyển chế độ tự động sang trạng thái off).
- Thiết kế lắp đặt để mô tơ chạy xuôi chạy ngược luôn (hiện tại người dùng chưa có cái này)

Bạn hãy tư vấn giải pháp cho tôi, và tư vấn các linh kiện cần thiết để mua, cũng như sơ dồ lắp đặt