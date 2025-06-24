/*
 * RGB LED Color Cycling (Basic Colors + Smooth Spectrum)
 * ------------------------------------------------------
 * This program demonstrates how to control an RGB LED using PWM.
 * It shows 8 basic colors, then smoothly transitions through a full-color spectrum.
 *
 * Hardware Setup:
 * - RED pin    → Digital PWM pin 9
 * - GREEN pin  → Digital PWM pin 10
 * - BLUE pin   → Digital PWM pin 11
 * - All LED pins should use current-limiting resistors (~220Ω recommended)
 * - Common Cathode LED is assumed. For Common Anode, invert the HIGH/LOW logic.
 */

const int RED_PIN = 9;    // Red LED pin
const int GREEN_PIN = 10; // Green LED pin
const int BLUE_PIN = 11;  // Blue LED pin

int DELAY_TIME = 500;     // Delay between color changes

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  displayAllBasicColors();  // Show 8 predefined colors
  showSpectrum();           // Show smooth rainbow transition
}

// Show 8 basic RGB combinations: off, red, green, blue, yellow, cyan, magenta, white
void displayAllBasicColors() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, HIGH);   // Red
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH); // Green
  digitalWrite(BLUE_PIN, LOW);
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);  // Blue
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, HIGH);   // Yellow (Red + Green)
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, LOW);    // Cyan (Green + Blue)
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, HIGH);   // Magenta (Red + Blue)
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  delay(DELAY_TIME);

  digitalWrite(RED_PIN, HIGH);   // White (All on)
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  delay(DELAY_TIME);
}

// Smooth transition through RGB spectrum (red → green → blue → red)
void showSpectrum() {
  for (int i = 0; i < 768; i++) {
    showRGB(i);      // Compute RGB values based on position in color wheel
    delay(10);
  }
}

// Convert index (0–767) to smooth RGB color values
void showRGB(int color) {
  int redPWM, greenPWM, bluePWM;

  if (color <= 255) {
    redPWM = 255 - color;   // Red to Green
    greenPWM = color;
    bluePWM = 0;
  } else if (color <= 511) {
    redPWM = 0;                      // Green to Blue
    greenPWM = 255 - (color - 256);
    bluePWM = color - 256;
  } else {
    redPWM = color - 512;           // Blue to Red
    greenPWM = 0;
    bluePWM = 255 - (color - 512);
  }

  analogWrite(RED_PIN, redPWM);
  analogWrite(GREEN_PIN, greenPWM);
  analogWrite(BLUE_PIN, bluePWM);
}
