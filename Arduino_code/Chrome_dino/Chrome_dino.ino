/*
  Automatic Dino Game Player using Servo Motor
  - This program controls a servo motor to press the "jump" key (spacebar or touchscreen)
    in the offline Chrome Dinosaur game.
  - Use a light sensor (e.g., LDR) or vibration sensor connected to pin A0 to detect obstacles.
  - Connect the servo motor signal wire to digital pin 9.
  - Connect the sensor as follows:
      + Sensor output to A0
      + GND and 5V to sensor power
  - The servo arm should be positioned to physically press the key or touchscreen when triggered.
*/

#include <Servo.h>

unsigned long startTime = 0;
Servo tab;

void setup() {
  Serial.begin(9600);
  tab.attach(9);  // Connect servo control wire to pin 9
}

void loop() {
  int angle;
  Serial.println(analogRead(A0));  // Read obstacle sensor value

  // If an obstacle is detected (light drops below threshold), make the dinosaur jump
  if (analogRead(A0) < 410) {
    angle = 10;              // Move servo to press the key
    startTime = millis();    // Record time of action
  }

  // Release the key after 50 milliseconds
  if ((millis() - startTime) > 50) {
    angle = 0;               // Reset servo position
  }

  tab.write(angle);          // Apply angle to servo
}
