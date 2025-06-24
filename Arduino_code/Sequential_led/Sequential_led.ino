/*
 * Sequential LED Light (Chaser Effect)
 * -------------------------------------
 * This code turns LEDs on and off one by one in a sequence,
 * creating a "running light" or "chaser" effect.
 *
 * Hardware Setup:
 * - Connect 8 LEDs to digital pins 2 through 9.
 * - Use 220Ω resistors in series with each LED.
 * - Connect the cathodes (–) of LEDs to GND.
 */

byte ledPin[] = {2, 3, 4, 5, 6, 7, 8, 9};  // Array of LED pins
byte pinCount;

void setup() {
  // Determine the number of LEDs in the array
  pinCount = sizeof(ledPin) / sizeof(ledPin[0]);

  // Set all pins as OUTPUT and turn LEDs off
  for (int i = 0; i < pinCount; i++) {
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  // Turn LEDs on one by one with delay
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPin[i], HIGH);
    delay(300);
  }

  // Turn LEDs off one by one with delay
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPin[i], LOW);
    delay(300);
  }
}
