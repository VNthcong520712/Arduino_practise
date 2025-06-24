/*
  Elevator Simulation with Motor Control and Encoder Feedback

  Wiring and Components:
  -----------------------
  Encoder:
    - Phase A connected to digital pin D2
    - Phase B connected to digital pin D9

  Floor Selection Buttons (active LOW; use INPUT_PULLUP):
    - Button for Floor 1 connected to analog pin A1
    - Button for Floor 2 connected to analog pin A2
    - Button for Floor 3 connected to analog pin A3
    - Button for Floor 4 connected to analog pin A4

  Set Position Button:
    - Connects to GND and analog pin A0 (used for homing the elevator)

  DC Motor:
    - Connected via motor driver (using AFMotor library)
    - The “white” wire is the external (output) connection and the “red” wire is the internal (input) side

  Notes:
  - The motor’s position is tracked by counting encoder pulses.
  - The number of pulses is converted into rotations (assumed 344 pulses per revolution).
  - The elevator’s simulated “floor” is determined by the number of rotations:
      • Less than 0.1 rotations => Position 0 (start/homing)
      • 0.1 to 0.3 rotations  => Floor 1
      • 1.1 to 1.3 rotations  => Floor 2
      • 2.1 to 2.3 rotations  => Floor 3
      • More than 3.1 rotations => Floor 4
  - When a button is pressed, the motor will move the elevator in the appropriate direction 
    (FORWARD if below the target floor, BACKWARD if above) until it reaches the desired floor.
*/

#include <AFMotor.h>

AF_DCMotor dcMotor(1);    // DC motor on channel 1

long pulseCount = 0;       // Encoder pulse count
int currentPosition;       // Elevator position (floor) determined by encoder feedback
int homeFlag = 0;          // Flag used to set initial position

const int phaseA = 2;      // Encoder Phase A connected to digital pin D2
const int phaseB = 9;      // Encoder Phase B connected to digital pin D9
const int interruptPin = 0;  // Interrupt pin for encoder pulses

#define posSet A0        // Set position button on analog pin A0

// Floor selection buttons (using analog pins with INPUT_PULLUP)
#define btnFloor1 A1     // Button for Floor 1
#define btnFloor2 A2     // Button for Floor 2
#define btnFloor3 A3     // Button for Floor 3
#define btnFloor4 A4     // Button for Floor 4

// Variables to store button states (0: not pressed, 1: pressed)
int btn1State, btn2State, btn3State, btn4State;
int lastBtn1State = 0, lastBtn2State = 0, lastBtn3State = 0, lastBtn4State = 0;

// Variables to indicate a new press event for each floor button
int press1 = 0, press2 = 0, press3 = 0, press4 = 0;

// Defined target positions in terms of encoder pulse rotations (example values)
const int floor1Target = 20;
const int floor2Target = 40;
const int floor3Target = 60;
const int floor4Target = 60;  // (Note: floor 3 and 4 share the same value in this example)

void setup() {
  Serial.begin(9600);

  // Set up floor button pins and the set-position pin as inputs with pull-up resistors
  pinMode(btnFloor1, INPUT_PULLUP);
  pinMode(btnFloor2, INPUT_PULLUP);
  pinMode(btnFloor3, INPUT_PULLUP);
  pinMode(btnFloor4, INPUT_PULLUP);
  pinMode(posSet, INPUT_PULLUP);

  dcMotor.setSpeed(150);
  dcMotor.run(FORWARD);
  delay(120);
  pulseCount = 0;

  // Attach interrupt to the designated pin (interruptPin, here 0) to count encoder pulses on falling edge
  attachInterrupt(interruptPin, countPulse, FALLING);
}

// Interrupt service routine to count encoder pulses
void countPulse() {
  // If Phase B is LOW, count down; otherwise, count up.
  if (digitalRead(phaseB) == 0) {
    pulseCount--;
  } else {
    pulseCount++;
  }
}

void loop() {
  // ----- Set Initial (Home) Position -----
  if (homeFlag < 1) {
    dcMotor.setSpeed(50);
    // Move elevator until the set-position sensor (A0) reads a value <= 500
    for (homeFlag; analogRead(posSet) > 500; homeFlag++) {
      dcMotor.run(BACKWARD);
    }
    if (analogRead(posSet) < 500) {
      dcMotor.run(RELEASE);  // Stop the motor once the sensor is triggered
    }
    pulseCount = 0;  // Reset encoder count after homing
  }

  // ----- Convert Encoder Pulses to Rotations & Determine Elevator Position -----
  float rotations = (float)pulseCount / 344;
  if (rotations < 0.1) {
    currentPosition = 0;  // Home
  } else if ((rotations > 0.1) && (rotations < 0.3)) {
    currentPosition = 1;  // Floor 1
  } else if ((rotations > 1.1) && (rotations < 1.3)) {
    currentPosition = 2;  // Floor 2
  } else if ((rotations > 2.1) && (rotations < 2.3)) {
    currentPosition = 3;  // Floor 3
  } else if (rotations > 3.1) {
    currentPosition = 4;  // Floor 4
  }

  // ----- Read and Convert Floor Button States -----
  // Buttons are active LOW; using analogRead for simulation, values < 300 indicate a press.
  btn1State = (analogRead(btnFloor1) > 300) ? 0 : 1;
  btn2State = (analogRead(btnFloor2) > 300) ? 0 : 1;
  btn3State = (analogRead(btnFloor3) > 300) ? 0 : 1;
  btn4State = (analogRead(btnFloor4) > 300) ? 0 : 1;

  // ----- Stop Motor at Limits -----
  // If the elevator is at the home position or at the top floor, stop the motor.
  if (currentPosition == 0 || currentPosition == 4) {
    dcMotor.setSpeed(0);
  }

  // ----- Detect New Button Presses (Edge Detection) -----
  if (btn1State == 1 && btn1State != lastBtn1State) {
    press1 = 1;
  }
  lastBtn1State = btn1State;

  if (btn2State == 1 && btn2State != lastBtn2State) {
    press2 = 1;
  }
  lastBtn2State = btn2State;

  if (btn3State == 1 && btn3State != lastBtn3State) {
    press3 = 1;
  }
  lastBtn3State = btn3State;

  if (btn4State == 1 && btn4State != lastBtn4State) {
    press4 = 1;
  }
  lastBtn4State = btn4State;

  // ----- Move Elevator to Floor 1 -----
  if (press1 == 1) {
    if (currentPosition == 1) {
      dcMotor.setSpeed(0);
      dcMotor.run(RELEASE);
      press1 = 0;
      delay(1000);
    } else if (currentPosition < 1) {
      dcMotor.setSpeed(850);
      dcMotor.run(FORWARD);
    } else if (currentPosition > 1) {
      dcMotor.setSpeed(70);
      dcMotor.run(BACKWARD);
    }
  }

  // ----- Move Elevator to Floor 2 -----
  if (press2 == 1) {
    if (currentPosition == 2) {
      dcMotor.setSpeed(0);
      dcMotor.run(RELEASE);
      press2 = 0;
      delay(1000);
    } else if (currentPosition < 2) {
      dcMotor.setSpeed(85);
      dcMotor.run(FORWARD);
    } else if (currentPosition > 2) {
      dcMotor.setSpeed(70);
      dcMotor.run(BACKWARD);
    }
  }

  // ----- Move Elevator to Floor 3 -----
  if (press3 == 1) {
    if (currentPosition == 3) {
      dcMotor.setSpeed(0);
      dcMotor.run(RELEASE);
      press3 = 0;
      delay(1000);
    } else if (currentPosition < 3) {
      dcMotor.setSpeed(85);
      dcMotor.run(FORWARD);
    } else if (currentPosition > 3) {
      dcMotor.setSpeed(70);
      dcMotor.run(BACKWARD);
    }
  }

  // ----- Move Elevator to Floor 4 -----
  if (press4 == 1) {
    if (currentPosition == 4) {
      dcMotor.setSpeed(0);
      dcMotor.run(RELEASE);
      press4 = 0;
      delay(1000);
    } else if (currentPosition < 4) {
      dcMotor.setSpeed(85);
      dcMotor.run(FORWARD);
    }
  }

  // ----- Output Debug Information -----
  Serial.print(rotations);
  Serial.print("   ");
  Serial.print(pulseCount);
  Serial.print("   ");
  Serial.println(currentPosition);
}
