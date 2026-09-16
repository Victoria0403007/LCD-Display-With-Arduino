#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Cursor Demo");
}

void loop() {
  // Display a solid block cursor
  lcd.setCursor(0, 1);
  lcd.print("Cursor: ON  ");
  lcd.cursor();
  delay(3000);
  
  // Switch to a blinking cursor
  lcd.setCursor(0, 1);
  lcd.print("Blink: ON   ");
  lcd.noCursor();
  lcd.blink();
  delay(3000);
  
  // Hide the cursor completely
  lcd.setCursor(0, 1);
  lcd.print("Cursor: OFF ");
  lcd.noBlink();
  delay(3000);
}