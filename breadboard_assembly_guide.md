# HƯỚNG DẪN LẮP RÁP BREADBOARD 830 - HỆ THỐNG BẠT XẾP THÔNG MINH

## 📋 MỤC LỤC
1. [Cấu trúc Breadboard 830](#1-cấu-trúc-breadboard-830)
2. [Nguyên tắc kết nối](#2-nguyên-tắc-kết-nối)
3. [Bước 1: Cắm Arduino Nano](#bước-1-cắm-arduino-nano)
4. [Bước 2: Nối nguồn vào Rails](#bước-2-nối-nguồn-vào-rails)
5. [Bước 3: Lắp điện trở Pull-up 10kΩ](#bước-3-lắp-điện-trở-pull-up-10kω)
6. [Bước 4: Lắp Buttons](#bước-4-lắp-buttons)
7. [Bước 5: Lắp điện trở + LED](#bước-5-lắp-điện-trở--led)
8. [Bước 6: Nối L298N](#bước-6-nối-l298n)
9. [Bước 7: Nối cảm biến mưa](#bước-7-nối-cảm-biến-mưa)
10. [Bước 8: Nối Limit Switches](#bước-8-nối-limit-switches)
11. [Layout tổng thể](#layout-tổng-thể)
12. [Checklist kiểm tra](#checklist-kiểm-tra)

---

## 1. CẤU TRÚC BREADBOARD 830

### Sơ đồ tổng quan:
```
┌────────────────────────────────────────────────────────────┐
│  [-] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [-]  │ ← Rail GND (nối dọc)
│  [+] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [+]  │ ← Rail +5V (nối dọc)
│                                                            │
│   a b c d e        f g h i j    ← Các cột chân cắm        │
│  ┌─────────┐     ┌─────────┐                              │
│ 1│● ● ● ● ●│     │● ● ● ● ●│1  ← Hàng 1                   │
│ 2│● ● ● ● ●│     │● ● ● ● ●│2  ← Hàng 2                   │
│ 3│● ● ● ● ●│     │● ● ● ● ●│3  ← Hàng 3                   │
│  │   ...   │ GAP │   ...   │                              │
│30│● ● ● ● ●│     │● ● ● ● ●│30 ← Hàng 30                  │
│  └─────────┘     └─────────┘                              │
│   ↑ a-e nối      ↑ f-j nối                                │
│     chung          chung                                   │
│                                                            │
│  [-] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [-]  │
│  [+] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [+]  │
└────────────────────────────────────────────────────────────┘
```

---

## 2. NGUYÊN TẮC KẾT NỐI

### ✅ QUY TẮC QUAN TRỌNG:

**Rail nguồn (+ và -):**
- Nối **DỌC** suốt chiều dài breadboard
- Rail (+) màu đỏ: +5V
- Rail (-) màu xanh/đen: GND

**Hàng ngang (1-30):**
- Mỗi hàng chia 2 nhóm: `a-b-c-d-e` và `f-g-h-i-j`
- Trong 1 nhóm: **NỐI CHUNG** với nhau
- Giữa 2 nhóm (e-f): **KHÔNG NỐI**

**Ví dụ:**
```
Hàng 5: a5-b5-c5-d5-e5 nối chung | f5-g5-h5-i5-j5 nối chung
        ↑ Nhóm 1                  ↑ Nhóm 2
        
e5 và f5 KHÔNG nối với nhau (GAP)
```

---

## BƯỚC 1: CẮM ARDUINO NANO

### Vị trí cắm:
Arduino Nano phải **VẮT QUA GAP GIỮA** (chân trái cột e, chân phải cột f)

```
   a  b  c  d  e  GAP  f  g  h  i  j
                ┌────┐
 8 │  │  │  │  │  │USB│  │  │  │  │  8
 9 │  │  │  │  │  │   │  │  │  │  │  9
10 │  │  │  │ [●══●───●══●] │  │  │  10  ← D13
11 │  │  │  │ [●══●───●══●] │  │  │  11  ← D12
12 │  │  │  │ [●══●───●══●] │  │  │  12  ← D11
13 │  │  │  │ [●══●───●══●] │  │  │  13  ← D10
14 │  │  │  │ [●══●───●══●] │  │  │  14  ← D9
15 │  │  │  │ [●══●───●══●] │  │  │  15  ← D8
   │  │  │  │  │  │   │  │  │  │  │
   ...Arduino Nano body (15 chân mỗi bên)...
   
25 │  │  │  │ [●══●───●══●] │  │  │  25  ← A0
26 │  │  │  │ [●══●───●══●] │  │  │  26  ← A1
27 │  │  │  │ [●══●───●══●] │  │  │  27  ← A2
   │  │  │  │  └────┘  │  │  │  │  │
                ↑       ↑
             Cột e    Cột f
```

### Cách cắm:
1. **Căn chỉnh:** Đặt Arduino Nano ngang breadboard, USB hướng ra ngoài
2. **Đặt vào GAP:** Chân trái Arduino vào cột **e**, chân phải vào cột **f**
3. **Ấn đều:** Ấn nhẹ 2 bên cho tất cả chân cắm đều vào breadboard
4. **Kiểm tra:** Tất cả chân phải ngang mặt breadboard (không lệch)

⚠️ **LƯU Ý:** Không ấn quá mạnh! Arduino có thể bị gãy chân.

---

## BƯỚC 2: NỐI NGUỒN VÀO RAILS

### Sơ đồ nguồn:
```
        Adapter 5V/3-5A
             │
        ┌────┴────┐
        │ (+)  (-) │
        └─┬────┬──┘
          │    │
          ↓    ↓
    [Rail +] [Rail -]  ← Cắm vào rails trên cùng
          │    │
          │    └──────┐
          │           │
    ┌─────┴─────┐     │
    │ Arduino   │     │
    │  5V  GND  │     │
    │  ●    ●   │←────┘
    └───────────┘
```

### Thực hiện:

**1. Nối Adapter vào Rails:**
```
Adapter (+) đỏ ──→ Rail (+) đỏ (trên cùng)
Adapter (-) đen ──→ Rail (-) đen (trên cùng)
```

**2. Nối Arduino 5V → Rail (+):**
- Jumper đỏ: Arduino chân **5V** (hàng X, cột e) → Rail (+)

**3. Nối Arduino GND → Rail (-):**
- Jumper đen: Arduino chân **GND** (hàng Y, cột e) → Rail (-)

### Map chân Arduino Nano:
```
Chân 5V: Hàng 27 (bên trái, cột e)
Chân GND: Hàng 14 và 29 (bên trái, cột e)
```

⚠️ **QUAN TRỌNG:** Kiểm tra cực tính adapter! (+) và (-) không được đảo!

---

## BƯỚC 3: LẮP ĐIỆN TRỞ PULL-UP 10kΩ

### Chức năng:
Pull-up resistor kéo signal lên 5V khi button/switch KHÔNG nhấn.

### Sơ đồ 1 pull-up (ví dụ button EXTEND - D6):

```
   Hàng  a  b  c  d  e  GAP  f  g  h  i  j
   
    1   │  │  │  │  │  │   │  │  │  │  │
        │  │ [Rail +]──┐  │  │  │  │  │  │  ← Nguồn 5V
    2   │  │  │  │ [10kΩ]  │  │  │  │  │  │
    3   │  │  │  │  └─┐│  │  │  │  │  │  │
    4   │  │  │  │  │ ││  │  │  │  │  │  │
    5   │  │  │ [Button]│  │● D6 Arduino │  ← Hàng 5
        │  │  │  │  │ └──jumper──┘│  │  │
    8   │  │  │ [Button]  │  │  │  │  │  │
        │  │  │  │  │  │  │  │  │  │  │  │
   10   │  │ [Rail -]──┘  │  │  │  │  │  │  ← GND
```

### Chi tiết kết nối:

**Button EXTEND (D6) - Hàng 5:**
1. 10kΩ chân 1 → Rail (+)
2. 10kΩ chân 2 → Hàng 2, cột d
3. Jumper: Hàng 2 cột d → Hàng 5 cột e (D6)
4. Button chân 1 → Hàng 5 cột c
5. Button chân 2 → Hàng 8 cột c
6. Jumper: Hàng 8 cột c → Rail (-)

**Lặp lại cho 6 inputs:**
- D6: Button EXTEND + 10kΩ (Hàng 5)
- D7: Button RETRACT + 10kΩ (Hàng 15)
- D8: Button STOP + 10kΩ (Hàng 16)
- D9: Button SMART + 10kΩ (Hàng 17)
- D10: Limit Switch 1 + 10kΩ (Hàng 13)
- D11: Limit Switch 2 + 10kΩ (Hàng 12)

---

## BƯỚC 4: LẮP BUTTONS

### Loại button breadboard:

```
    Chân 1 ● ─── ● Chân 2
           │     │
    Chân 3 ● ─── ● Chân 4
    
    Khi NHẤN: Chân 1-2 và 3-4 nối thông
    Khi KHÔNG: Tất cả ngắt
```

### Cắm button vào breadboard:

**Button 4 chân (tiêu chuẩn):**
```
   a  b  c  d  e
   
 5 │  │ ●[Button]●  ← Chân 1,2 hàng 5
   │  │  │ GAP │  │
 8 │  │ ●[Button]●  ← Chân 3,4 hàng 8
```

**Button 2 chân (mini):**
```
   a  b  c  d  e
   
 5 │  │  ●[Btn]  ← Chân 1 hàng 5
   │  │   │  │  │
 8 │  │  ●[Btn]  ← Chân 2 hàng 8
```

### Vị trí 4 buttons:
- Button EXTEND: Hàng 5-8
- Button RETRACT: Hàng 15-18
- Button STOP: Hàng 16-19 (lệch 1 hàng)
- Button SMART: Hàng 17-20

---

## BƯỚC 5: LẮP ĐIỆN TRỞ + LED

### Sơ đồ 1 LED (ví dụ LED_EXTEND - D13):

```
   Hàng  a  b  c  d  e  GAP  f  g  h  i  j
                      ┌──────────┐
   10   │  │  │  │ ●←│● D13 Arduino│  ← D13
        │  │  │  │ ├jumper┤  │  │  │
   12   │  │  │ [220Ω] │  │  │  │  │  │
        │  │  │  └┬┘│  │  │  │  │  │  │
   15   │  │ [LED +]─┘  │  │  │  │  │  │  ← Anode (chân dài)
   16   │  │ [LED -] │  │  │  │  │  │  │  ← Cathode (chân ngắn)
        │  │  │  │  │  │  │  │  │  │  │
   18   │  │ [Rail -]──┘  │  │  │  │  │  │  ← GND
```

### Chi tiết kết nối LED:

**LED_EXTEND (D13) - Hàng 10:**
1. Jumper: D13 Arduino (hàng 10, cột e) → Hàng 12 cột d
2. 220Ω chân 1: Hàng 12 cột c
3. 220Ω chân 2: Hàng 15 cột c
4. LED chân dài (+): Hàng 15 cột b
5. LED chân ngắn (-): Hàng 16 cột b
6. Jumper: Hàng 16 cột b → Rail (-)

**Nhận biết cực LED:**
```
LED 5mm:
    _____
   /     \     ← Đầu tròn
  |   +   |    
  |       |    
  |_______|
   │     │
   │     └─── Chân ngắn (-) Cathode
   └───────── Chân dài (+) Anode
```

**Lặp lại cho 6 LED:**
- D13 → LED_EXTEND + 220Ω
- A1 → LED_RETRACT + 220Ω
- A2 → LED_STOP + 220Ω
- A3 → LED_SMART + 220Ω
- A4 → LED_RED + 220Ω
- A5 → LED_GREEN + 220Ω

---

## BƯỚC 6: NỐI L298N

### L298N đặt BÊN NGOÀI breadboard:

```
┌─────────────────────┐
│    L298N MODULE     │
│                     │
│ VCC  GND  EN IN1 IN2│
│  ●    ●   ●  ●   ●  │
└──┬────┬───┬──┬───┬──┘
   │    │   │  │   │
   │    │   │  │   └──→ Arduino D4 (hàng 18, cột e)
   │    │   │  └──────→ Arduino D3 (hàng 19, cột e)
   │    │   └─────────→ Arduino D2 (hàng 20, cột e)
   │    └─────────────→ Arduino GND (Rail -)
   └──────────────────→ Adapter 5V (+) hoặc Rail (+)
   
┌──────────────┐
│ OUT1    OUT2 │  ← Nối motor 2 dây vào đây
└──────────────┘
```

### Kết nối jumper:

**Từ Arduino → L298N:**
1. **D2 (EN)**: Jumper từ D2 (hàng 20, cột e) → L298N EN
2. **D3 (IN1)**: Jumper từ D3 (hàng 19, cột e) → L298N IN1
3. **D4 (IN2)**: Jumper từ D4 (hàng 18, cột e) → L298N IN2
4. **GND**: Jumper từ Rail (-) → L298N GND

**Từ Adapter → L298N:**
5. **VCC**: Jumper từ Rail (+) → L298N VCC (5V)

**Motor → L298N:**
6. **Motor wire 1** → L298N OUT1
7. **Motor wire 2** → L298N OUT2

⚠️ **LƯU Ý:** Motor 2 dây không cần phân biệt cực (+/-). Nếu quay ngược thì đổi dây.

---

## BƯỚC 7: NỐI CẢM BIẾN MƯA

### Rain Sensor FC-37:

```
┌──────────────────┐
│ Rain Sensor      │
│ Module FC-37     │
│                  │
│ VCC GND DO AO    │
│  ●   ●   ●  ●    │
└──┬───┬───┬──┬───┘
   │   │   │  │
   │   │   │  └─────→ Arduino A0 (hàng 25, cột e)
   │   │   └────────→ Arduino D12 (hàng 11, cột e)
   │   └────────────→ Rail (-)
   └────────────────→ Rail (+) 5V
```

### Kết nối jumper:

1. **VCC**: Rain sensor VCC → Rail (+)
2. **GND**: Rain sensor GND → Rail (-)
3. **DO**: Rain sensor DO → Arduino D12 (hàng 11, cột e)
4. **AO**: Rain sensor AO → Arduino A0 (hàng 25, cột e)

⚠️ **LƯU Ý:** Sensor pad (tấm cảm biến) nối với module qua cable 4 dây.

---

## BƯỚC 8: NỐI LIMIT SWITCHES

### Limit Switch (Normally Open - NO):

```
Switch 1 (LIMIT_EXTENDED - D10):

   Rail (+) ──┬── [10kΩ] ──┬── Arduino D10
              │            │
         [Switch NO]       │
              │            │
           Rail (-)────────┘
           
Khi KHÔNG nhấn: D10 = HIGH (qua 10kΩ)
Khi NHẤN: D10 = LOW (nối GND)
```

### Kết nối:

**Switch 1 (D10) - Hàng 13:**
1. 10kΩ đã lắp từ Bước 3 (Rail + → D10)
2. Switch chân 1 → Hàng 13 cột c (ngang D10)
3. Switch chân 2 → Rail (-)
4. Jumper: Hàng 13 cột c → Hàng 13 cột e (D10)

**Switch 2 (D11) - Hàng 12:**
- Tương tự như Switch 1

⚠️ **LƯU Ý:** Limit switches lắp ở 2 đầu hành trình bạt (kéo hết và thu hết).

---

## LAYOUT TỔNG THỂ

### Breadboard hoàn chỉnh:

```
┌────────────────────────────────────────────────────────────┐
│  [-] ━━━[Adapter GND]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [-]  │
│  [+] ━━━[Adapter +5V]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [+]  │
│                                                            │
│  Hàng 1-7:                                                 │
│  ├─ Button circuits (4 nút)                               │
│  └─ Pull-up resistors 10kΩ (6 cái)                        │
│                                                            │
│  Hàng 8-27:   ┌─────────────────────────┐                 │
│               │   ARDUINO NANO (USB↑)   │                 │
│               │  Vắt qua GAP (e-f)      │                 │
│               └─────────────────────────┘                 │
│  ├─ D2-D13: Motor + Buttons + LEDs                        │
│  ├─ A0: Rain sensor analog                                │
│  └─ A1-A5: LEDs output                                    │
│                                                            │
│  Hàng 28-30:                                               │
│  └─ LED circuits + resistors 220Ω (6 cái)                 │
│                                                            │
│  [-] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [-]  │
│  [+] ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  [+]  │
└────────────────────────────────────────────────────────────┘

BÊN NGOÀI BREADBOARD:
┌──────────────┐       ┌──────────────┐
│  L298N       │───────│ Motor 5V TT  │
│  (jumpers)   │       └──────────────┘
└──────────────┘
        
┌──────────────┐       ┌──────────────┐
│ Rain Sensor  │───────│ Sensor Pad   │
│  FC-37       │       │ (ngoài trời) │
└──────────────┘       └──────────────┘

┌──────────────┐       ┌──────────────┐
│ Limit SW1    │       │ Limit SW2    │
│ (Extended)   │       │ (Retracted)  │
└──────────────┘       └──────────────┘
```

### Màu dây khuyến nghị:

| Chức năng | Màu dây |
|-----------|---------|
| +5V       | Đỏ      |
| GND       | Đen     |
| Signal    | Xanh/Vàng/Trắng |
| Motor     | Vàng/Xanh đậm |

---

## CHECKLIST KIỂM TRA

### ✅ TRƯỚC KHI CẤP NGUỒN:

**1. Kiểm tra visual:**
- [ ] Arduino cắm vắt qua GAP (e-f)
- [ ] Tất cả chân Arduino cắm đều vào breadboard
- [ ] Rails (+) và (-) đã nối nguồn
- [ ] Không có dây chập chéo

**2. Kiểm tra bằng multimeter:**
- [ ] Đo điện trở Rail (+) ↔ Rail (-): Phải ≥ 1MΩ (không short)
- [ ] Đo điện trở Arduino 5V ↔ GND: Phải ≥ 500kΩ
- [ ] Kiểm tra adapter: +5V ±0.2V (4.8-5.2V)
- [ ] Kiểm tra cực tính: (+) đỏ, (-) đen

**3. Kiểm tra kết nối:**
- [ ] Tất cả LED có nối 220Ω (không nối trực tiếp)
- [ ] Tất cả buttons/switches có 10kΩ pull-up
- [ ] L298N GND nối chung với Arduino GND
- [ ] Motor nối vào L298N OUT1/OUT2

### ✅ SAU KHI CẤP NGUỒN:

**1. Nguồn điện:**
- [ ] Arduino LED power sáng
- [ ] Adapter không nóng bất thường (<40°C)
- [ ] Đo điện áp Rails: +5V ±0.2V

**2. Test từng phần:**
- [ ] Upload code test → Serial Monitor 9600 baud
- [ ] Nhấn từng button → Serial log hiển thị
- [ ] Chạm nước lên rain sensor → giá trị thay đổi
- [ ] Nhấn limit switches → Serial log hiển thị
- [ ] Test motor 2 chiều (không tải) → quay mượt

**3. Kiểm tra LED:**
- [ ] Tất cả 6 LED sáng khi code test chạy
- [ ] LED không quá sáng (có 220Ω) hoặc mờ

**4. An toàn:**
- [ ] Không có linh kiện nóng bất thường
- [ ] Không ngửi thấy mùi cháy
- [ ] Motor dừng khi nhấn STOP
- [ ] Limit switches tự động dừng motor

---

## 🚨 TROUBLESHOOTING

### ❌ Arduino không bật:
- Kiểm tra USB cable
- Kiểm tra nguồn 5V từ adapter
- Đo điện áp chân 5V Arduino: phải ~5V

### ❌ LED không sáng:
- Kiểm tra cực LED (chân dài là +)
- Kiểm tra điện trở 220Ω đã cắm chưa
- Đo điện áp 2 đầu LED: phải ~2V

### ❌ Button không hoạt động:
- Kiểm tra 10kΩ pull-up đã cắm chưa
- Đo điện áp chân Arduino khi KHÔNG nhấn: phải ~5V
- Đo điện áp chân Arduino khi NHẤN: phải ~0V

### ❌ Motor không chạy:
- Kiểm tra L298N có nguồn 5V chưa
- Kiểm tra GND chung: Arduino-L298N-Adapter
- Đổi 2 dây motor nếu quay ngược
- Test motor trực tiếp: nối 2 dây vào 5V và GND

### ❌ Arduino nóng:
- ⚠️ TẮT NGUỒN NGAY!
- Có chập mạch: kiểm tra lại tất cả kết nối
- Kiểm tra không có dây chạm nhầm Rails

---

## 📝 TIPS QUAN TRỌNG

### 💡 Mẹo lắp ráp:

1. **Lắp từng phần, test từng phần:**
   - Cắm Arduino → Test
   - Nối nguồn → Test điện áp
   - Lắp 1 button → Test code
   - Lắp 1 LED → Test sáng
   - Lặp lại cho tất cả

2. **Dùng màu dây chuẩn:**
   - Đỏ: +5V
   - Đen: GND
   - Các màu khác: Signal

3. **Label dây:**
   - Dán nhãn giấy vào jumper
   - Ghi: "D6-BTN1", "A0-RAIN", etc.

4. **Chụp ảnh từng bước:**
   - Chụp khi lắp xong mỗi phần
   - Dễ quay lại kiểm tra khi có lỗi

### 🔧 Công cụ cần có:

- [ ] Multimeter (đo điện áp, điện trở)
- [ ] Nhíp/Kìm nhỏ (gắp linh kiện)
- [ ] Kéo cắt dây
- [ ] Băng dính nhãn
- [ ] Hộp đựng linh kiện nhỏ

### 📖 Tài liệu tham khảo:

- Arduino Nano Pinout: [Google "Arduino Nano pinout"]
- Breadboard tutorial: YouTube "How to use breadboard"
- Datasheet L298N: [Google "L298N datasheet"]

---

**🎉 CHÚC BẠN LẮP RÁP THÀNH CÔNG!**

Nếu gặp vấn đề, hãy:
1. Kiểm tra lại checklist
2. Đo điện áp các điểm quan trọng
3. Test từng phần riêng biệt
4. Chụp ảnh breadboard để so sánh

**⚠️ AN TOÀN:** Luôn tắt nguồn khi lắp/tháo linh kiện!
