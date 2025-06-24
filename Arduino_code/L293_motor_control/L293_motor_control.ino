/*
 * Arduino RC Car with Joystick Control and RGB LED Effects
 * ----------------------------------------------------------
 * This project reads joystick input from analog pins A0 and A1,
 * and controls two DC motors via the AFMotor library.
 *
 * The A5 pin is used as a button to cycle LED lighting modes:
 *   - Mode 0: All LEDs off
 *   - Mode 1: Police lights (flashing red & blue)
 *   - Mode 2: Rainbow fade effect
 *   - Mode 3: Color cycling of RGB LEDs
 *
 * Connections:
 *   - Joystick X-axis: A0
 *   - Joystick Y-axis: A1
 *   - Mode button: A5 (active LOW with INPUT_PULLUP)
 *   - RGB LEDs:
 *       RED: Pin 9
 *       GREEN: Pin 10
 *       BLUE: Pin 2
 *   - Motors connected via Adafruit Motor Shield channels M1 and M3
 */

#include <AFMotor.h>

#define JOY_X A0
#define JOY_Y A1

int i = 0;
int a = 0;
int lastStatus = 1;
int StatusA;
int StatusD;
int RED = 9;
int GREEN = 10;
int BLUE = 2;
unsigned long timedelay = 0;

byte speedxt = 0;
byte speedxl = 0;
byte speedyp = 0;
byte speedyt = 0;
int docx = 0;
int docy = 0;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT_PULLUP); // Button input
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);

  motor1.setSpeed(200);
  motor3.setSpeed(200);
  motor1.run(RELEASE);
  motor3.run(RELEASE);
}

void loop() {
  docx = analogRead(JOY_X);
  docy = analogRead(JOY_Y);

  // ---------------- Toggle LED Modes with Button ----------------
  StatusA = analogRead(A5);
  StatusD = (StatusA < 20) ? 0 : 1;
  if (StatusD == 0 && StatusD != lastStatus) {
    i++;
  }
  lastStatus = StatusD;

  if (i % 4 == 1) police();
  else if (i % 4 == 2) rainbow();
  else if (i % 4 == 3) colorful();
  else {
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
  }

  // ---------------- Map Joystick Values ----------------
  if (docx >= 517) speedxl = map(docx, 517, 1023, 0, 200);
  if (docx <= 517) speedxt = map(docx, 517, 0, 0, 200);
  if (docy >= 517) speedyt = map(docy, 517, 1023, 0, 200);
  if (docy <= 517) speedyp = map(docy, 517, 0, 0, 200);

  // ---------------- Motor Control ----------------
  if (speedxt > 70) forward();
  else if (speedxl > 70) backward();
  else if (speedyp > 70) right();
  else if (speedyt > 70) left();

  // ---------------- Stop Motors if No Input ----------------
  if (speedxt <= 70 && speedxl <= 70 && speedyp <= 70 && speedyt <= 70) {
    motor1.run(RELEASE);
    motor3.run(RELEASE);
    Serial.println("Stopped");
  }

  // ---------------- Debugging Output ----------------
  Serial.print("Forward: ");
  Serial.print(speedxt);
  Serial.print("  Backward: ");
  Serial.print(speedxl);
  Serial.print("  Right: ");
  Serial.print(speedyp);
  Serial.print("  Left: ");
  Serial.println(speedyt);
}

// ---------------- Movement Functions ----------------
void forward() {
  Serial.println("Forward");
  motor1.setSpeed(speedxt);
  motor3.setSpeed(speedxt);
  motor1.run(FORWARD);
  motor3.run(FORWARD);
}

void backward() {
  Serial.println("Backward");
  motor1.setSpeed(speedxl);
  motor3.setSpeed(speedxl);
  motor1.run(BACKWARD);
  motor3.run(BACKWARD);
}

void right() {
  Serial.println("Right");
  motor1.setSpeed(speedyp);
  motor3.setSpeed(speedyp);
  motor3.run(RELEASE);
  motor1.run(BACKWARD);
}

void left() {
  Serial.println("Left");
  motor1.setSpeed(speedyt);
  motor3.setSpeed(speedyt);
  motor3.run(BACKWARD);
  motor1.run(RELEASE);
}

// ---------------- LED Modes ----------------
void police() {
  if ((unsigned long)(millis() - timedelay) >= 90) {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
    if ((unsigned long)(millis() - timedelay) >= 450) {
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
      if ((unsigned long)(millis() - timedelay) >= 720) {
        digitalWrite(RED, HIGH);
        digitalWrite(BLUE, LOW);
        if ((unsigned long)(millis() - timedelay) >= 1170) {
          digitalWrite(RED, LOW);
          digitalWrite(BLUE, LOW);
          if ((unsigned long)(millis() - timedelay) >= 1620) {
            digitalWrite(BLUE, HIGH);
            digitalWrite(RED, LOW);
            if ((unsigned long)(millis() - timedelay) >= 1890) {
              digitalWrite(BLUE, LOW);
              digitalWrite(RED, LOW);
              if ((unsigned long)(millis() - timedelay) >= 1980) {
                digitalWrite(BLUE, HIGH);
                digitalWrite(RED, LOW);
                if ((unsigned long)(millis() - timedelay) >= 2340) {
                  digitalWrite(BLUE, LOW);
                  digitalWrite(RED, LOW);
                  timedelay = millis();
                }
              }
            }
          }
        }
      }
    }
  }
  Serial.println("Police mode");
}

void rainbow() {
  digitalWrite(BLUE, LOW);
  if (a < 511 && millis() - timedelay >= 2) {
    showRGB(a++);
    timedelay = millis();
  }
  if (a == 511) a = 0;
}

void showRGB(int color) {
  int redPWM, greenPWM;
  if (color <= 255) {
    redPWM = 255 - color;
    greenPWM = color;
  } else {
    redPWM = color - 255;
    greenPWM = 255 - (color - 256);
  }
  analogWrite(RED, redPWM);
  analogWrite(GREEN, greenPWM);
}

void colorful() {
  if (millis() - timedelay >= 500 * 8) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    timedelay = millis();
  } else if (millis() - timedelay >= 500 * 7) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
  } else if (millis() - timedelay >= 500 * 6) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
  } else if (millis() - timedelay >= 500 * 5) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  } else if (millis() - timedelay >= 500 * 4) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
  } else if (millis() - timedelay >= 500 * 3) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  } else if (millis() - timedelay >= 500 * 2) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  } else if (millis() - timedelay >= 500) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
}
