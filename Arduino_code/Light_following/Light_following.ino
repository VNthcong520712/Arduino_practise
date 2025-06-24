/*
 * Solar Panel Sun Tracker Using LDRs and Servo Motor
 * ---------------------------------------------------
 * This program adjusts a solar panel's angle based on light detected by two LDR sensors (photoresistors).
 * It uses a servo motor to rotate the panel toward the brighter side.
 *
 * Hardware Setup:
 * - LDR (Left sensor) connected to analog pin A0
 * - LDR (Right sensor) connected to analog pin A1
 * - Both LDRs form a voltage divider with a fixed resistor
 * - Servo motor signal connected to digital pin 9
 * - Power the servo and sensors appropriately
 */

#include <Servo.h>

Servo trx;           // Servo motor object
int dh = 0;          // Current angle of the servo

void setup() {
  trx.attach(9);     // Attach the servo signal to pin 9
  Serial.begin(9600);
  trx.write(90);     // Start at center position
  dh = 90;
}

void loop() {
  int left = analogRead(A0);   // Read left LDR
  int right = analogRead(A1);  // Read right LDR
  int avg = (left + right) / 2; // Average light intensity

  // Print diagnostic values to Serial Monitor
  Serial.print("Left - Right: ");
  Serial.print(left - right);
  Serial.print("   Right - Left: ");
  Serial.print(right - left);
  Serial.print("   Left - Avg: ");
  Serial.print(left - avg);
  Serial.print("   Right - Avg: ");
  Serial.println(right - avg);

  // Adjust servo angle based on light difference
  if (abs(left - avg) > 15 || abs(right - avg) > 15) {
    if ((left - avg) > (right - avg)) {
      // Light is stronger on the left → rotate left
      if (dh > 0) {
        dh -= 2;
        delay(1);
        trx.write(dh);
      }
    } else if ((left - avg) < (right - avg)) {
      // Light is stronger on the right → rotate right
      if (dh < 180) {
        dh += 2;
        delay(1);
        trx.write(dh);
      }
    }
  }

  Serial.print("Current Angle: ");
  Serial.println(dh);
}
