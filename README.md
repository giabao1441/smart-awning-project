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
1. **Motor không chạy** → Check nguồn 5V, L298N connections, GND chung
2. **Button không hoạt động** → Check pull-up resistors 10kΩ, debounce
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

**⚠️ Disclaimer**: Đây là dự án DIY mô hình demo. Nếu thực hiện cho bạt thật kích thước lớn, nên nhờ thợ chuyên môn hỗ trợ phần 220V và motor công suất cao.