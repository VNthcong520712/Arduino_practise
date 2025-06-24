/*
 * Rotary Encoder RPM Measurement with Interrupt
 * ---------------------------------------------
 * Hardware Setup:
 * - Connect the encoder's VCC (positive) pin to 3.3V.
 * - Phase A (output A) to digital pin D2 (interrupt pin 0).
 * - Phase B (output B) to digital pin D3.
 *
 * Functionality:
 * - This code uses an interrupt on phase A to count encoder pulses.
 * - It calculates and prints the RPM and frequency (Hz) every second.
 * - Direction is determined using the state of phase B.
 *
 * Note:
 * - It assumes 345 pulses per revolution (change this number if needed).
 */

const int interrupt0 = 0;     // Interrupt number for pin D2 (phase A)
const int phase_a = 2;        // Phase A of the encoder
const int phase_b = 3;        // Phase B of the encoder

int rpm = 0;                  // Rotations per minute
unsigned long lastmillis = 0;

float pulse = 0;              // Pulse count
float i = 0;                  // Frequency counter (Hz)

void setup() {
  attachInterrupt(interrupt0, int_, FALLING);  // Trigger on falling edge of phase A
  pinMode(phase_a, INPUT_PULLUP);
  pinMode(phase_b, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Calculate RPM and frequency every 1 second
  if (millis() - lastmillis >= 1000) {
    noInterrupts(); // Prevent changes during calculation
    rpm = i * 60;   // Convert Hz to RPM
    Serial.print("RPM =\t");
    Serial.print(rpm);
    Serial.print("\tHz =\t");
    Serial.println(i);
    i = 0;                  // Reset frequency count
    lastmillis = millis();  // Update timestamp
    interrupts();           // Re-enable interrupts
  }
}

void int_() {
  // Encoder direction and step counting
  if (digitalRead(phase_b) == LOW) {
    pulse++;
    if (pulse == 345) {  // Full rotation forward
      i++;
      pulse = 0;
    }
  } else {
    pulse--;
    if (pulse == -1) {  // Full rotation backward
      i--;
      pulse = 344;
    }
  }
}
