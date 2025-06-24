/*
  Stepper Motor Test with Arduino (Using Stepper Library)
  --------------------------------------------------------
  Description:
  This sketch tests a unipolar stepper motor using the built-in Stepper library.
  The motor is controlled via four digital pins and will rotate a specific number of revolutions.
  The current revolution count is printed to the Serial Monitor.

  Wiring (Stepper Motor to Arduino):
  ----------------------------------
  - IN1  -> D8
  - IN2  -> D9
  - IN3  -> D10
  - IN4  -> D11

  Notes:
  ------
  - The motor completes one full revolution in 2048 steps.
  - Motor speed is set to 23 RPM.
  - It will rotate in reverse direction (-steps) for 123 revolutions.

  Libraries Required:
  -------------------
  - Stepper (built-in with Arduino IDE)
*/

#include <Stepper.h>

const long stepsPerRevolution = 2048; // Number of steps per full rotation
int vong = 1;                          // Counter for number of rotations

// Initialize two stepper motor instances (using the same pins)
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);           // Start serial communication
  myStepper.setSpeed(23);       // Set motor speed to 23 RPM
  myStepper2.setSpeed(23);      // Optional: set speed for second instance
}

void loop() {
  if (vong < 123) {
    myStepper2.step(-stepsPerRevolution); // Rotate one full turn in reverse
    vong++;
    Serial.println(vong);                 // Print current turn count
  }
}
