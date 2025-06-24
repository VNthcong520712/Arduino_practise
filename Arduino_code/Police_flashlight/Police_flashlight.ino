/*
 * Police LED Flashing Light Simulation
 * -------------------------------------
 * This code simulates flashing red and blue lights like a police siren.
 *
 * Hardware Setup:
 * - Red LED connected to digital pin 9
 * - Blue LED connected to digital pin 11
 * - Use current-limiting resistors (~220Ω) for each LED
 */

int redPin = 9;    // Red LED pin
int bluePin = 11;  // Blue LED pin

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Flash red LED twice
  digitalWrite(redPin, HIGH);
  digitalWrite(bluePin, LOW);
  delay(270);
  digitalWrite(redPin, LOW);
  delay(90);

  digitalWrite(redPin, HIGH);
  delay(270);
  digitalWrite(redPin, LOW);
  delay(90);

  delay(80); // Short pause before switching to blue

  // Flash blue LED twice
  digitalWrite(bluePin, HIGH);
  delay(270);
  digitalWrite(bluePin, LOW);
  delay(90);

  digitalWrite(bluePin, HIGH);
  delay(270);
  digitalWrite(bluePin, LOW);
  delay(90);
}
