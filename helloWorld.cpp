#include <LiquidCrystal.h>

// Pin Assignments
const int TEMP_SENSOR_PIN = A0; // Analog input for temperature sensor
const int POT_PIN = A1;         // Analog input for setpoint potentiometer
const int FAN_PIN = 9;          // PWM output for fan control
const int BUZZER_PIN = 8;       // Digital output for buzzer alert

// Initialize LCD (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Climate Control");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Read Potentiometer to set desired temperature (range: 20°C to 40°C)
  int potValue = analogRead(POT_PIN);
  float setpointTemp = map(potValue, 0, 1023, 20, 40);

  // 2. Read TMP36 Temperature Sensor (converting voltage to °C)
  int rawSensor = analogRead(TEMP_SENSOR_PIN);
  float voltage = rawSensor * (5.0 / 1023.0);
  float currentTemp = (voltage - 0.5) * 100.0; // TMP36 scale formula

  // 3. Climate Control Logic
  if (currentTemp > setpointTemp + 5.0) {
    // Overheat condition: Fan at HIGH speed + Audible Alert
    analogWrite(FAN_PIN, 255);
    digitalWrite(BUZZER_PIN, HIGH);
    
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print((int)currentTemp); lcd.print("C  Set:"); lcd.print((int)setpointTemp); lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("STATE: OVERHEAT ");

  } else if (currentTemp > setpointTemp) {
    // Warm condition: Fan at MODERATE speed, No Buzzer
    analogWrite(FAN_PIN, 150);
    digitalWrite(BUZZER_PIN, LOW);
    
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print((int)currentTemp); lcd.print("C  Set:"); lcd.print((int)setpointTemp); lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("STATE: COOLING  ");

  } else {
    // Normal condition: Fan OFF, No Buzzer
    analogWrite(FAN_PIN, 0);
    digitalWrite(BUZZER_PIN, LOW);
    
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print((int)currentTemp); lcd.print("C  Set:"); lcd.print((int)setpointTemp); lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("STATE: NORMAL   ");
  }

  delay(500); // Refresh rate
}