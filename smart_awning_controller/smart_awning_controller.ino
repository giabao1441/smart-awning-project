/*
 * HỆ THỐNG BẠT XẾP THÔNG MINH HOÀN CHỈNH
 * - Điều khiển motor xuôi/ngược
 * - Giao diện 4 nút bấm (KÉO/THU/STOP/SMART)
 * - Tự động theo thời tiết
 * - Ưu tiên lệnh từ người dùng
 */

#include <Arduino.h>

// =================== CHÂN KẾT NỐI MOTOR ===================
#define MOTOR_ENABLE 6        // Enable motor (PWM)
#define MOTOR_IN1 7           // Motor direction 1
#define MOTOR_IN2 8           // Motor direction 2

// =================== CHÂN INPUT - NÚT BẤM ===================
#define BTN_EXTEND 12         // Nút KÉO bạt
#define BTN_RETRACT 10        // Nút THU bạt
#define BTN_STOP 9           // Nút STOP
#define BTN_SMART_MODE 2      // Nút chế độ thông minh

// =================== CHÂN SENSOR ===================
#define LIMIT_EXTENDED 4     // Limit switch - bạt kéo hết
#define LIMIT_RETRACTED 5    // Limit switch - bạt thu hết
#define RAIN_SENSOR_ANALOG A6  // Cảm biến mưa (analog)

// =================== CHÂN OUTPUT - LED ===================
#define LED_EXTEND A2         // LED nút KÉO
#define LED_RETRACT A1        // LED nút THU  
#define LED_STOP A0           // LED nút STOP
#define LED_SMART_MODE A3     // LED nút SMART MODE
#define LED_STATUS_RED A4     // LED trạng thái - đỏ
#define LED_STATUS_GREEN A5   // LED trạng thái - xanh lá

// =================== BIẾN TRẠNG THÁI ===================
bool smartModeEnabled = true;  // Bật chế độ smart mặc định khi khởi động
bool awningExtended = false;
bool awningRetracted = false;
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
const unsigned long MOTOR_MAX_RUNTIME = 6000;    // 6 giây tối đa

// =================== NGƯỠNG CẢM BIẾN ===================
const int RAIN_THRESHOLD = 400;        // Ngưỡng phát hiện mưa
const int RAIN_THRESHOLD_CLEAR = 500;  // Ngưỡng hết mưa (hysteresis)
const int MOTOR_SPEED = 255;           // Tốc độ motor (0-255)
const unsigned long RAIN_STOP_DELAY = 3000; // Delay 3 giây sau khi hết mưa

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
SystemMode currentSystemMode = MODE_AUTO;  // Bắt đầu ở chế độ AUTO

void setup() {
  Serial.begin(9600);
  
  // =================== CẤU HÌNH INPUT PINS ===================
  pinMode(BTN_EXTEND, INPUT_PULLUP);
  pinMode(BTN_RETRACT, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_SMART_MODE, INPUT_PULLUP);
  pinMode(LIMIT_EXTENDED, INPUT_PULLUP);
  pinMode(LIMIT_RETRACTED, INPUT_PULLUP);
  
  // =================== CẤU HÌNH OUTPUT PINS ===================
  // Motor control
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
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
  // === FAST CHECKS - Chạy mỗi vòng loop ===
  // Các function này có debounce/interval riêng để tránh spam:
  // - checkButtonInputs: debounce 100ms
  // - checkLimitSwitches: chỉ update khi thay đổi
  // - checkMotorTimeout: chỉ check khi motor đang chạy
  checkButtonInputs();      // Debounce 100ms - responsive cho user
  checkLimitSwitches();     // Safety - dừng motor ngay khi chạm limit
  checkMotorTimeout();      // Safety - timeout protection

  unsigned long currentTime = millis();
  
  // === CHU KỲ CHÍNH - Chạy mỗi 300ms ===
  if (currentTime - lastLoopTime < LOOP_INTERVAL) {
    return;  // Chưa đủ 300ms, bỏ qua phần còn lại
  }
  
  lastLoopTime = currentTime;
  
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
  int rawExtend = digitalRead(BTN_EXTEND);
  int rawRetract = digitalRead(BTN_RETRACT);
  int rawStop = digitalRead(BTN_STOP);
  int rawSmart = digitalRead(BTN_SMART_MODE);
  
  bool currentExtend = !rawExtend;
  bool currentRetract = !rawRetract;
  bool currentStop = !rawStop;
  bool currentSmart = !rawSmart;
  
  // DEBUG: In giá trị RAW để phát hiện lỗi hardware
  static unsigned long lastDebugPrint = 0;
  // if (millis() - lastDebugPrint > 2000) {
  //   Serial.print("🔍 RAW PINS: Extend=");
  //   Serial.print(rawExtend);
  //   Serial.print(" Retract=");
  //   Serial.print(rawRetract);
  //   Serial.print(" Stop=");
  //   Serial.print(rawStop);
  //   Serial.print(" Smart=");
  //   Serial.println(rawSmart);
  //   lastDebugPrint = millis();
  // }

  // Nếu KHÔNG có thay đổi gì → return sớm
  if ((currentExtend == btnExtendPressed)
    && (currentRetract == btnRetractPressed)
    && (currentStop == btnStopPressed)
    && (currentSmart == btnSmartPressed)) {
      lastButtonCheck = millis();
      return;
  }
  
  // Edge detection: chỉ toggle khi VỪA NHẤN (chưa nhấn trước đó)
  if (currentSmart && !btnSmartPressed) {
    smartModeEnabled = !smartModeEnabled;
    currentSystemMode = smartModeEnabled ? MODE_AUTO : MODE_MANUAL;
    
    Serial.print("🔄 Smart Mode: ");
    Serial.println(smartModeEnabled ? "ENABLED" : "DISABLED");
    
    if (!smartModeEnabled && motorRunning) {
      stopMotor(); // Dừng motor khi tắt auto mode
    }
  }
  
  // Cập nhật trạng thái nút bấm
  btnExtendPressed = currentExtend;
  btnRetractPressed = currentRetract; 
  btnStopPressed = currentStop;
  btnSmartPressed = currentSmart;
  
  Serial.println("================= BUTTON STATUS ================");
  Serial.print("🧠 Smart Status: "); Serial.println(btnSmartPressed ? "/\\" : "___");
  Serial.print("🔓 Extend Status: "); Serial.println(btnExtendPressed ? "/\\" : "___");
  Serial.print("🔒 Retract Status: "); Serial.println(btnRetractPressed ? "/\\" : "___");
  Serial.print("🚫 Stop Status: "); Serial.println(btnStopPressed ? "/\\" : "___");
  Serial.println("================= BUTTON STATUS ================");
  
  lastButtonCheck = millis();
}

void checkRainSensor() {
  if (millis() - lastRainCheck < RAIN_CHECK_INTERVAL) return;
  
  int rainAnalog = analogRead(RAIN_SENSOR_ANALOG);
  
  // Hysteresis: khác ngưỡng khi bắt đầu mưa vs hết mưa
  bool rainDetected;
  if (isRaining) {
    // Đang mưa → Ngưỡng cao hơn (500) để tránh dao động
    rainDetected = (rainAnalog < RAIN_THRESHOLD_CLEAR);
  } else {
    // Không mưa → Ngưỡng thấp hơn (400) để phát hiện mưa
    rainDetected = (rainAnalog < RAIN_THRESHOLD);
  }
  
  Serial.print(rainDetected ? "WET rainDetected" : "DRY rainDetected");
  Serial.print(" (Analog: ");
  Serial.print(rainAnalog);
  Serial.println(")");

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
    
    // Serial.print(" (Analog: ");
    // Serial.print(rainAnalog);
    // Serial.print(", Digital: ");
    // Serial.print(rainDigital ? "WET" : "DRY");
    // Serial.println(")");
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
  if (btnExtendPressed) {
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
  if (btnRetractPressed) {
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
  if (isRaining) {
    startExtendMotor();
    Serial.println("🌧️ AUTO EXTEND - Rain detected");
    rainJustStopped = false; // Reset flag
  }
  // Tự động thu bạt khi hết mưa - với delay
  else if (!isRaining && rainJustStopped) {
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
  
  // Kiểm tra limit switch trước khi start motor (LOW = đã chạm với INPUT_PULLUP)
  bool limitReached = (digitalRead(LIMIT_EXTENDED) == LOW);
  if (limitReached) {
    Serial.println("⚠️ Already at extended limit - cannot extend further");
    awningExtended = true;
    stopMotor();
    return;
  }
  
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
  
  // Kiểm tra limit switch trước khi start motor
  if (!digitalRead(LIMIT_RETRACTED)) {
    Serial.println("⚠️ Already at retracted limit - cannot retract further");
    awningRetracted = true;
    stopMotor();
    return;
  }
  
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

  if (millis() - lastStatusUpdate < STATUS_UPDATE_INTERVAL) return;
  
  // LED trạng thái motor và chế độ
  digitalWrite(LED_EXTEND, (currentMotorState == MOTOR_EXTENDING) ? HIGH : LOW);
  digitalWrite(LED_RETRACT, (currentMotorState == MOTOR_RETRACTING) ? HIGH : LOW);
  digitalWrite(LED_STOP, btnStopPressed ? HIGH : LOW);
  digitalWrite(LED_SMART_MODE, smartModeEnabled ? HIGH : LOW);
  
  
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
  // Serial.print("Position - Extended: ");
  // Serial.print(awningExtended ? "YES" : "NO");
  // Serial.print(", Retracted: ");
  // Serial.println(awningRetracted ? "YES" : "NO");
  // Serial.print("Rain Detected: ");
  // Serial.println(isRaining ? "YES" : "NO");
  // Serial.print("Buttons - Extend: ");
  // Serial.print(btnExtendPressed ? "ON" : "OFF");
  // Serial.print(", Retract: ");
  // Serial.print(btnRetractPressed ? "ON" : "OFF");
  // Serial.print(", Stop: ");
  // Serial.print(btnStopPressed ? "ON" : "OFF");
  // Serial.print(", Smart: ");
  // Serial.println(smartModeEnabled ? "ON" : "OFF");
  // Serial.println("====================\n");
}