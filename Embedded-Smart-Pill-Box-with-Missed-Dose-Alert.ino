#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin definitions
#define BUZZER_PIN 6
#define LED_PIN 3
#define TOUCH_SENSOR_PIN 2
#define LID_SERVO_PIN_1 9
#define IR_SENSOR_PIN 5

// Initialize RTC
RTC_DS3231 rtc;

// Initialize LCD (address, columns, rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize servos
Servo lidServo1;
Servo lidServo2;

// Servo movement variables
const int SERVO_DELAY = 30;   
const int SERVO_STEP = 2;     

// Time variables
unsigned long startTime = 0;
bool morningMed = false;
bool afternoonMed = false;
bool nightMed = false;
bool alarmActive = false;
String currentMedicineTime = "";

// Function declarations
void activateAlarm(String message);
void deactivateAlarm();
bool checkMedicineTaken();
void openBox();
void closeBox();
void moveServosSlowly(int targetAngle);

void setup() {

  Serial.begin(9600);

  // Initialize pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);

  // Initialize servos
  lidServo1.attach(LID_SERVO_PIN_1);
  lidServo2.attach(LID_SERVO_PIN_1);

  // Initial position
  lidServo1.write(0);
  lidServo2.write(0);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Med Box Active");

  // Initialize RTC
  if (!rtc.begin()) {
    lcd.setCursor(0, 1);
    lcd.print("RTC Error!");
    while (1);
  }

  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  startTime = millis();

  lcd.setCursor(0, 1);
  lcd.print("Ready!");
  delay(2000);
}

void loop() {

  DateTime now = rtc.now();

  if (!alarmActive) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");

    if (now.hour() < 10) lcd.print("0");
    lcd.print(now.hour());
    lcd.print(":");

    if (now.minute() < 10) lcd.print("0");
    lcd.print(now.minute());
    lcd.print(":");

    if (now.second() < 10) lcd.print("0");
    lcd.print(now.second());

    lcd.setCursor(0, 1);
    lcd.print("Date: ");
    lcd.print(now.day());
    lcd.print("/");
    lcd.print(now.month());
    lcd.print("/");
    lcd.print(now.year());
  }

  unsigned long currentTime = millis();
  unsigned long elapsedSeconds =
      (currentTime - startTime) / 1000;

  // Morning reminder
  if (!morningMed && elapsedSeconds >= 60) {
    currentMedicineTime = "Morning";
    activateAlarm("Morning Medicine!");
    morningMed = true;
  }

  // Afternoon reminder
  if (!afternoonMed && elapsedSeconds >= 120) {
    currentMedicineTime = "Afternoon";
    activateAlarm("Afternoon Medicine!");
    afternoonMed = true;
  }

  // Night reminder
  if (!nightMed && elapsedSeconds >= 180) {
    currentMedicineTime = "Night";
    activateAlarm("Night Medicine!");
    nightMed = true;
  }

  // Open box using touch sensor
  if (alarmActive &&
      digitalRead(TOUCH_SENSOR_PIN) == HIGH) {

    openBox();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Take your");

    lcd.setCursor(0, 1);
    lcd.print(currentMedicineTime +
              " medicine");

    if (checkMedicineTaken()) {

      digitalWrite(LED_PIN,
                   !digitalRead(LED_PIN));

      tone(BUZZER_PIN, 1000, 200);
      delay(500);
    }

    deactivateAlarm();
  }

  delay(200);
}

void activateAlarm(String message) {

  alarmActive = true;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REMINDER:");

  lcd.setCursor(0, 1);
  lcd.print(message);

  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000);
}

void deactivateAlarm() {

  alarmActive = false;

  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Medicine taken!");

  lcd.setCursor(0, 1);
  lcd.print("Thank you!");

  delay(2000);

  closeBox();
}

bool checkMedicineTaken() {

  return digitalRead(IR_SENSOR_PIN) == HIGH;
}

void openBox() {

  moveServosSlowly(180);
}

void closeBox() {

  moveServosSlowly(0);
}

void moveServosSlowly(int targetAngle) {

  int currentPos1 =
      lidServo1.read();

  if (targetAngle > currentPos1) {

    for (int pos = currentPos1;
         pos <= targetAngle;
         pos += SERVO_STEP) {

      lidServo1.write(pos);
      delay(SERVO_DELAY);
    }

  } else {

    for (int pos = currentPos1;
         pos >= targetAngle;
         pos -= SERVO_STEP) {

      lidServo1.write(pos);
      delay(SERVO_DELAY);
    }
  }

  lidServo1.write(targetAngle);
}