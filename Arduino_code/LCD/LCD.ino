/*
 * I2C LCD Display Example with Custom Heart Symbol
 * ------------------------------------------------
 * This sketch displays a romantic sequence of messages on a 16x2 I2C LCD.
 * It also shows a custom heart animation moving across the screen.
 *
 * Hardware Connections:
 * - SDA → A4 (on Arduino UNO)
 * - SCL → A5 (on Arduino UNO)
 *
 * Required Library:
 * - LiquidCrystal_I2C by Frank de Brabander or similar
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD with I2C address 0x27, and dimensions 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Custom heart character (pixel art in 5x8 format)
byte heart[8] = {
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
  B00000
};

void setup() {
  lcd.init();             // Initialize LCD
  lcd.backlight();        // Turn on backlight
  lcd.clear();            // Clear screen
  lcd.createChar(1, heart); // Register heart symbol in slot 1

  // Display a sequence of romantic messages
  lcd.setCursor(0, 0);
  lcd.print("Hey you ...");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Yes, it's you ...");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("You ......");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Do you want ...");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("To be ...");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("To be my lover?");
  lcd.setCursor(0, 1);
  lcd.print("Yes or Yes?");
  delay(1300);
  lcd.clear();

  // Display "I LOVE YOU" with heart animation
  lcd.setCursor(3, 0);
  lcd.print("I LOVE YOU");
  for (int i = 0; i <= 15; i++) {
    lcd.setCursor(i, 1);
    lcd.write(1); // Draw heart symbol
    delay(200);
  }

  delay(2000);
  lcd.clear();
  delay(300);
}

void loop() {
  // No action in loop; all messages shown in setup()
}
