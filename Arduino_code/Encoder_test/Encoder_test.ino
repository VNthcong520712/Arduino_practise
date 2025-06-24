/*
 * Rotary Encoder Basic Test with Interrupt
 * ----------------------------------------
 * This code tests a rotary encoder by reading its A and B phase signals.
 * It uses an interrupt to detect changes on phase A (falling edge),
 * determines rotation direction using phase B,
 * and counts the number of steps.
 * 
 * Hardware Connections:
 * - Encoder Phase A → Pin 2 (interrupt 0)
 * - Encoder Phase B → Pin 3
 * - Common ground of encoder → GND
 * - VCC of encoder (usually 5V) → 5V
 * 
 * Serial Monitor will display:
 * - Current state of phase A and B
 * - Incremented/decremented counter based on rotation direction
 */

int phaA = 2;       // Phase A (connected to interrupt 0 / pin 2)
int phaB = 3;       // Phase B (connected to pin 3)
int value = 0;      // Step counter

void setup() {
  attachInterrupt(0, doc, FALLING);  // Interrupt on falling edge of Phase A
  pinMode(phaA, INPUT_PULLUP);       // Use internal pull-up resistors
  pinMode(phaB, INPUT_PULLUP);
  Serial.begin(9600);                // Start Serial Monitor
}

void loop() {
  // Nothing needed here, all handled in interrupt
}

void doc() {
  // Determine rotation direction based on Phase B
  if (digitalRead(phaB) == LOW) {
    value++;  // Clockwise
  } else {
    value--;  // Counter-clockwise
  }

  // Print phase states and current value
  Serial.print("Phase A: ");
  Serial.print(digitalRead(phaA));
  Serial.print("  Phase B: ");
  Serial.print(digitalRead(phaB));
  Serial.print("  Counter: ");
  Serial.println(value);
}
