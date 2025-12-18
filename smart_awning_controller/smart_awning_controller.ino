/*
 * HỆ THỐNG BẠT XẾP THÔNG MINH HOÀN CHỈNH
 * - Điều khiển motor xuôi/ngược
 * - Giao diện 4 nút bấm (KÉO/THU/STOP/SMART)
 * - Tự động theo thời tiết
 * - Ưu tiên lệnh từ người dùng
 */

#include <Arduino.h>

// =================== CHÂN KẾT NỐI MOTOR ===================
#define MOTOR_ENABLE 2        // Enable motor (PWM)
#define MOTOR_IN1 3           // Motor direction 1
#define MOTOR_IN2 4           // Motor direction 2
#define MOTOR_POWER_RELAY 5   // Relay nguồn motor chính

// =================== CHÂN INPUT - NÚT BẤM ===================
#define BTN_EXTEND 6          // Nút KÉO bạt
#define BTN_RETRACT 7         // Nút THU bạt
#define BTN_STOP 8            // Nút STOP
#define BTN_SMART_MODE 9      // Nút chế độ thông minh

// =================== CHÂN SENSOR ===================
#define LIMIT_EXTENDED 10     // Limit switch - bạt kéo hết
#define LIMIT_RETRACTED 11    // Limit switch - bạt thu hết
#define RAIN_SENSOR_DIGITAL 12 // Cảm biến mưa (digital)
#define RAIN_SENSOR_ANALOG A0  // Cảm biến mưa (analog)

// =================== CHÂN OUTPUT - LED ===================
#define LED_EXTEND 13         // LED nút KÉO
#define LED_RETRACT A1        // LED nút THU  
#define LED_STOP A2           // LED nút STOP
#define LED_SMART_MODE A3     // LED nút SMART MODE
#define LED_STATUS_RED A4     // LED trạng thái - đỏ
#define LED_STATUS_GREEN A5   // LED trạng thái - xanh lá

// =================== BIẾN TRẠNG THÁI ===================
bool smartModeEnabled = false;
bool awningExtended = false;
bool awningRetracted = true;
bool isRaining = false;
bool motorRunning = false;
bool systemEnabled = true;

// =================== TRẠNG THÁI NÚT BẤM ===================
bool btnExtendPressed = false;
bool btnRetractPressed = false;
bool btnStopPressed = false;
bool btnSmartPressed = false;

// =================== THỜI GIAN VÀ DEBOUNCE ===================
unsigned long lastButtonCheck = 0;
unsigned long lastRainCheck = 0;
unsigned long lastStatusUpdate = 0;
unsigned long lastLoopTime = 0;                  // Chu kỳ loop chính
unsigned long motorStartTime = 0;
unsigned long rainStoppedTime = 0;              // Thời điểm hết mưa
unsigned long buttonPressTime[4] = {0, 0, 0, 0}; // Debounce cho 4 nút
bool rainJustStopped = false;                    // Flag để track trạng thái chuyển

const unsigned long DEBOUNCE_TIME = 100;          // Debounce cho nút bấm
const unsigned long LOOP_INTERVAL = 300;          // Chu kỳ loop chính (300ms)
const unsigned long RAIN_CHECK_INTERVAL = 2000;  // Check mưa mỗi 2s
const unsigned long STATUS_UPDATE_INTERVAL = 500; // Cập nhật LED mỗi 0.5s
const unsigned long MOTOR_MAX_RUNTIME = 60000;    // 60 giây tối đa

// =================== NGƯỠNG CẢM BIẾN ===================
const int RAIN_THRESHOLD = 400;        // Ngưỡng phát hiện mưa
const int RAIN_THRESHOLD_CLEAR = 500;  // Ngưỡng hết mưa (hysteresis)
const int MOTOR_SPEED = 255;           // Tốc độ motor (0-255)
const unsigned long RAIN_STOP_DELAY = 120000; // Delay 2 phút sau khi hết mưa

// =================== ENUM TRẠNG THÁI ===================
enum MotorState {
  MOTOR_STOPPED,
  MOTOR_EXTENDING,
  MOTOR_RETRACTING
};

enum SystemMode {
  MODE_MANUAL,
  MODE_AUTO
};

MotorState currentMotorState = MOTOR_STOPPED;
SystemMode currentSystemMode = MODE_MANUAL;

void setup() {
  Serial.begin(9600);
  
  // =================== CẤU HÌNH INPUT PINS ===================
  pinMode(BTN_EXTEND, INPUT_PULLUP);
  pinMode(BTN_RETRACT, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_SMART_MODE, INPUT_PULLUP);
  pinMode(LIMIT_EXTENDED, INPUT_PULLUP);
  pinMode(LIMIT_RETRACTED, INPUT_PULLUP);
  pinMode(RAIN_SENSOR_DIGITAL, INPUT_PULLUP);
  
  // =================== CẤU HÌNH OUTPUT PINS ===================
  // Motor control
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_POWER_RELAY, OUTPUT);
  
  // LED indicators  
  pinMode(LED_EXTEND, OUTPUT);
  pinMode(LED_RETRACT, OUTPUT);
  pinMode(LED_STOP, OUTPUT);
  pinMode(LED_SMART_MODE, OUTPUT);
  pinMode(LED_STATUS_RED, OUTPUT);
  pinMode(LED_STATUS_GREEN, OUTPUT);
  
  // =================== KHỞI TẠO TRẠNG THÁI ===================
  stopMotor();
  updateLEDStatus();
  
  // Đọc vị trí ban đầu từ limit switches
  awningExtended = !digitalRead(LIMIT_EXTENDED);
  awningRetracted = !digitalRead(LIMIT_RETRACTED);
  
  Serial.println("🏠 ===================================");
  Serial.println("🏠 SMART AWNING SYSTEM STARTED");
  Serial.println("🏠 Complete motor control + 4 buttons");
  Serial.println("🏠 ===================================");
  Serial.println("📋 Controls:");
  Serial.println("   - EXTEND: Kéo bạt ra");
  Serial.println("   - RETRACT: Thu bạt lại");  
  Serial.println("   - STOP: Dừng ngay");
  Serial.println("   - SMART: Bật/tắt chế độ tự động");
  Serial.println();
  
  // Hiệu ứng khởi động
  startupSequence();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Chỉ xử lý sau mỗi LOOP_INTERVAL (300ms)
  if (currentTime - lastLoopTime < LOOP_INTERVAL) {
    // === FAST CHECKS (Critical timing) ===
    // Những function này cần check thường xuyên vì liên quan đến:
    // - User experience (buttons)
    // - Safety (limit switches, timeout)
    checkButtonInputs();      // Debounce 100ms - responsive cho user
    checkLimitSwitches();     // Safety - dừng motor ngay khi chạm limit
    checkMotorTimeout();      // Safety - timeout protection
    delay(10);                // Nghỉ 10ms để không spam CPU
    return;
  }
  
  lastLoopTime = currentTime;
  
  // === CHU KỲ CHÍNH (300ms) ===
  // Kiểm tra cảm biến
  checkRainSensor();          // Check mỗi 2s (có interval riêng)
  
  // Xử lý logic điều khiển
  processButtonCommands();    // Xử lý lệnh từ user
  processAutoMode();          // Xử lý chế độ tự động
  
  // Cập nhật đầu ra
  updateLEDStatus();          // Cập nhật LED (có interval riêng)
  updateMotorControl();       // Cập nhật motor (hiện tại trống)
}

// =================== KIỂM TRA ĐẦU VÀO ===================
void checkButtonInputs() {
  if (millis() - lastButtonCheck < DEBOUNCE_TIME) return; // Debounce 100ms
  
  // Đọc trạng thái nút bấm (LOW = pressed)
  bool currentExtend = !digitalRead(BTN_EXTEND);
  bool currentRetract = !digitalRead(BTN_RETRACT);
  bool currentStop = !digitalRead(BTN_STOP);
  bool currentSmart = !digitalRead(BTN_SMART_MODE);
  
  // Xử lý nút SMART MODE (toggle)
  static bool lastSmartState = false;
  if (currentSmart && !lastSmartState) {
    smartModeEnabled = !smartModeEnabled;
    currentSystemMode = smartModeEnabled ? MODE_AUTO : MODE_MANUAL;
    
    Serial.print("🔄 Smart Mode: ");
    Serial.println(smartModeEnabled ? "ENABLED" : "DISABLED");
    
    if (!smartModeEnabled && motorRunning) {
      stopMotor(); // Dừng motor khi tắt auto mode
    }
  }
  lastSmartState = currentSmart;
  
  // Cập nhật trạng thái nút bấm
  btnExtendPressed = currentExtend;
  btnRetractPressed = currentRetract; 
  btnStopPressed = currentStop;
  
  lastButtonCheck = millis();
}

void checkRainSensor() {
  if (millis() - lastRainCheck < RAIN_CHECK_INTERVAL) return;
  
  int rainAnalog = analogRead(RAIN_SENSOR_ANALOG);
  bool rainDigital = !digitalRead(RAIN_SENSOR_DIGITAL);
  
  // Hysteresis: khác ngưỡng khi bắt đầu mưa vs hết mưa
  bool rainDetected;
  if (isRaining) {
    // Đang mưa → cần analog < RAIN_THRESHOLD_CLEAR để xác nhận hết mưa
    rainDetected = (rainAnalog < RAIN_THRESHOLD_CLEAR) && !rainDigital ? false : true;
  } else {
    // Không mưa → cần analog > RAIN_THRESHOLD để xác nhận có mưa
    rainDetected = (rainAnalog > RAIN_THRESHOLD) || rainDigital;
  }
  
  if (rainDetected != isRaining) {
    isRaining = rainDetected;
    
    // Track thời điểm hết mưa để delay retract
    if (!isRaining) {
      rainStoppedTime = millis();
      rainJustStopped = true;
      Serial.println("🌧️ Rain STOPPED - Starting delay before retract");
    } else {
      rainJustStopped = false;
      Serial.println("🌧️ Rain DETECTED - Will extend awning");
    }
    
    Serial.print(" (Analog: ");
    Serial.print(rainAnalog);
    Serial.print(", Digital: ");
    Serial.print(rainDigital ? "WET" : "DRY");
    Serial.println(")");
  }
  
  lastRainCheck = millis();
}

void checkLimitSwitches() {
  bool extended = !digitalRead(LIMIT_EXTENDED);
  bool retracted = !digitalRead(LIMIT_RETRACTED);
  
  if (extended != awningExtended || retracted != awningRetracted) {
    awningExtended = extended;
    awningRetracted = retracted;
    
    Serial.print("📍 Position: ");
    if (awningExtended) Serial.println("FULLY EXTENDED");
    else if (awningRetracted) Serial.println("FULLY RETRACTED");
    else Serial.println("MIDDLE POSITION");
    
    // Tự động dừng motor khi chạm limit switch
    if ((awningExtended && currentMotorState == MOTOR_EXTENDING) ||
        (awningRetracted && currentMotorState == MOTOR_RETRACTING)) {
      stopMotor();
      Serial.println("⏹️ Auto-stopped at limit position");
    }
  }
}

void checkMotorTimeout() {
  if (motorRunning && (millis() - motorStartTime > MOTOR_MAX_RUNTIME)) {
    stopMotor();
    Serial.println("⚠️ Motor timeout - stopped for safety");
  }
}

// =================== XỬ LÝ LỆNH ĐIỀU KHIỂN ===================
void processButtonCommands() {
  // Ưu tiên: STOP > EXTEND/RETRACT
  if (btnStopPressed) {
    if (motorRunning) {
      stopMotor();
      Serial.println("🛑 MANUAL STOP - User command");
      
      // Tắt auto mode khi user can thiệp
      if (smartModeEnabled) {
        smartModeEnabled = false;
        currentSystemMode = MODE_MANUAL;
        Serial.println("� Auto mode disabled due to manual intervention");
      }
    }
    return;
  }
  
  // Lệnh EXTEND
  if (btnExtendPressed && !motorRunning) {
    if (!awningExtended) {
      startExtendMotor();
      Serial.println("📤 MANUAL EXTEND - User command");
      
      // Tắt auto mode khi user can thiệp
      if (smartModeEnabled) {
        smartModeEnabled = false;
        currentSystemMode = MODE_MANUAL;
        Serial.println("� Auto mode disabled due to manual intervention");
      }
    } else {
      Serial.println("ℹ️ Already fully extended");
    }
  }
  
  // Lệnh RETRACT
  if (btnRetractPressed && !motorRunning) {
    if (!awningRetracted) {
      startRetractMotor();
      Serial.println("� MANUAL RETRACT - User command");
      
      // Tắt auto mode khi user can thiệp
      if (smartModeEnabled) {
        smartModeEnabled = false;
        currentSystemMode = MODE_MANUAL;
        Serial.println("💡 Auto mode disabled due to manual intervention");
      }
    } else {
      Serial.println("ℹ️ Already fully retracted");
    }
  }
}

void processAutoMode() {
  if (!smartModeEnabled || motorRunning) return;
  
  // Tự động kéo bạt khi mưa
  if (isRaining && !awningExtended) {
    startExtendMotor();
    Serial.println("🌧️ AUTO EXTEND - Rain detected");
    rainJustStopped = false; // Reset flag
  }
  // Tự động thu bạt khi hết mưa - với delay
  else if (!isRaining && awningExtended && rainJustStopped) {
    // Kiểm tra đã đủ thời gian delay chưa
    if (millis() - rainStoppedTime >= RAIN_STOP_DELAY) {
      startRetractMotor();
      Serial.print("☀️ AUTO RETRACT - Rain stopped ");
      Serial.print(RAIN_STOP_DELAY / 1000);
      Serial.println("s ago");
      rainJustStopped = false; // Reset flag
    } else {
      // Hiển thị thời gian còn lại (mỗi 10s)
      static unsigned long lastDelayLog = 0;
      if (millis() - lastDelayLog > 10000) {
        unsigned long remaining = (RAIN_STOP_DELAY - (millis() - rainStoppedTime)) / 1000;
        Serial.print("⏳ Waiting ");
        Serial.print(remaining);
        Serial.println("s before auto-retract");
        lastDelayLog = millis();
      }
    }
  }
}

// =================== ĐIỀU KHIỂN MOTOR ===================
void startExtendMotor() {
  if (awningExtended) return;
  
  digitalWrite(MOTOR_POWER_RELAY, HIGH); // Bật nguồn motor
  delay(100);
  
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENABLE, MOTOR_SPEED);
  
  currentMotorState = MOTOR_EXTENDING;
  motorRunning = true;
  motorStartTime = millis();
  
  Serial.println("⚡ Motor EXTENDING started");
}

void startRetractMotor() {
  if (awningRetracted) return;
  
  digitalWrite(MOTOR_POWER_RELAY, HIGH); // Bật nguồn motor
  delay(100);
  
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  analogWrite(MOTOR_ENABLE, MOTOR_SPEED);
  
  currentMotorState = MOTOR_RETRACTING;
  motorRunning = true;
  motorStartTime = millis();
  
  Serial.println("⚡ Motor RETRACTING started");
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENABLE, 0);
  
  delay(500); // Đợi motor dừng hoàn toàn
  digitalWrite(MOTOR_POWER_RELAY, LOW); // Tắt nguồn motor
  
  currentMotorState = MOTOR_STOPPED;
  motorRunning = false;
  
  Serial.println("⏹️ Motor STOPPED");
}

void updateMotorControl() {
  // Function này có thể mở rộng thêm logic điều khiển motor
  // Hiện tại logic chính đã được xử lý ở các hàm khác
}

// =================== CẬP NHẬT LED ===================
void updateLEDStatus() {
  if (millis() - lastStatusUpdate < STATUS_UPDATE_INTERVAL) return;
  
  // LED nút bấm
  digitalWrite(LED_EXTEND, btnExtendPressed ? HIGH : LOW);
  digitalWrite(LED_RETRACT, btnRetractPressed ? HIGH : LOW);
  digitalWrite(LED_STOP, btnStopPressed ? HIGH : LOW);
  digitalWrite(LED_SMART_MODE, smartModeEnabled ? HIGH : LOW);
  
  // LED trạng thái hệ thống
  if (motorRunning) {
    // Nhấp nháy khi motor đang chạy
    bool blink = (millis() / 300) % 2;
    digitalWrite(LED_STATUS_RED, blink);
    digitalWrite(LED_STATUS_GREEN, !blink);
  } else if (smartModeEnabled) {
    // Xanh lá sáng ở chế độ auto
    digitalWrite(LED_STATUS_RED, LOW);
    digitalWrite(LED_STATUS_GREEN, HIGH);
  } else {
    // Đỏ sáng ở chế độ manual
    digitalWrite(LED_STATUS_RED, HIGH);
    digitalWrite(LED_STATUS_GREEN, LOW);
  }
  
  lastStatusUpdate = millis();
}

// =================== HIỆU ỨNG KHỞI ĐỘNG ===================
void startupSequence() {
  Serial.println("🔄 System initializing...");
  
  // Kiểm tra tất cả LED
  digitalWrite(LED_EXTEND, HIGH);
  digitalWrite(LED_RETRACT, HIGH);
  digitalWrite(LED_STOP, HIGH);
  digitalWrite(LED_SMART_MODE, HIGH);
  digitalWrite(LED_STATUS_RED, HIGH);
  digitalWrite(LED_STATUS_GREEN, HIGH);
  delay(1000);
  
  // Tắt tất cả LED
  digitalWrite(LED_EXTEND, LOW);
  digitalWrite(LED_RETRACT, LOW);
  digitalWrite(LED_STOP, LOW);
  digitalWrite(LED_SMART_MODE, LOW);
  digitalWrite(LED_STATUS_RED, LOW);
  digitalWrite(LED_STATUS_GREEN, LOW);
  delay(500);
  
  // Hiệu ứng chạy dần
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_EXTEND, HIGH);
    delay(200);
    digitalWrite(LED_EXTEND, LOW);
    digitalWrite(LED_RETRACT, HIGH);
    delay(200);
    digitalWrite(LED_RETRACT, LOW);
    digitalWrite(LED_STOP, HIGH);
    delay(200);
    digitalWrite(LED_STOP, LOW);
    digitalWrite(LED_SMART_MODE, HIGH);
    delay(200);
    digitalWrite(LED_SMART_MODE, LOW);
  }
  
  Serial.println("✅ System ready!");
}

// =================== FUNCTIONS DEBUG ===================
void printSystemStatus() {
  Serial.println("\n=== SYSTEM STATUS ===");
  Serial.print("Smart Mode: ");
  Serial.println(smartModeEnabled ? "ENABLED" : "DISABLED");
  Serial.print("Motor State: ");
  switch(currentMotorState) {
    case MOTOR_STOPPED: Serial.println("STOPPED"); break;
    case MOTOR_EXTENDING: Serial.println("EXTENDING"); break;
    case MOTOR_RETRACTING: Serial.println("RETRACTING"); break;
  }
  Serial.print("Position - Extended: ");
  Serial.print(awningExtended ? "YES" : "NO");
  Serial.print(", Retracted: ");
  Serial.println(awningRetracted ? "YES" : "NO");
  Serial.print("Rain Detected: ");
  Serial.println(isRaining ? "YES" : "NO");
  Serial.print("Buttons - Extend: ");
  Serial.print(btnExtendPressed ? "ON" : "OFF");
  Serial.print(", Retract: ");
  Serial.print(btnRetractPressed ? "ON" : "OFF");
  Serial.print(", Stop: ");
  Serial.print(btnStopPressed ? "ON" : "OFF");
  Serial.print(", Smart: ");
  Serial.println(smartModeEnabled ? "ON" : "OFF");
  Serial.println("====================\n");
}