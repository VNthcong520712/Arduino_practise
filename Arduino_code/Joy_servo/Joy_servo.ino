/*
 * Joystick Control for Two Servos (X and Y Axis)
 * -----------------------------------------------
 * This program reads analog input from a joystick module and
 * controls two servos based on X and Y movement.
 *
 * Hardware Connections:
 * - Joystick X-axis → Analog pin A1
 * - Joystick Y-axis → Analog pin A0
 * - Servo X (horizontal) → Digital pin 11
 * - Servo Y (vertical) → Digital pin 10
 * - Make sure to power the servos with sufficient current (use external 5V if needed)
 */

#define JOY_X A1
#define JOY_Y A0

#include <Servo.h>

Servo x;  // Servo for X axis
Servo y;  // Servo for Y axis

int joy_x_value;  // Raw analog value from joystick X
int joy_y_value;  // Raw analog value from joystick Y

void setup() {
  Serial.begin(9600);     // Start serial communication
  x.attach(11);           // Attach horizontal servo to pin 11
  y.attach(10);           // Attach vertical servo to pin 10
  x.write(90);            // Initialize to center position
  y.write(90);
}

void loop() {
  int servo_x_pos;
  int servo_y_pos;

  // Read analog values from joystick
  joy_x_value = analogRead(JOY_X);
  joy_y_value = analogRead(JOY_Y);

  // Print joystick values to Serial Monitor
  Serial.print("Joystick X: ");
  Serial.print(joy_x_value);
  Serial.print("   ");
  Serial.print("Joystick Y: ");
  Serial.println(joy_y_value);

  // Map joystick values (0–1023) to servo angles (0–180)
  servo_x_pos = map(joy_x_value, 0, 1023, 0, 180);
  servo_y_pos = map(joy_y_value, 0, 1023, 0, 180);

  // Send position to servos
  x.write(servo_x_pos);
  y.write(servo_y_pos);
}
