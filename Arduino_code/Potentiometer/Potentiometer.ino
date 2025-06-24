/*
 * Reading a Potentiometer (Variable Resistor) with Arduino
 * ---------------------------------------------------------
 * This program reads an analog voltage from pin A0, converts it to:
 *   - A raw ADC value (0–1023)
 *   - A voltage in volts (0–5V)
 *   - An estimated resistance value (0–10kΩ)
 *
 * Hardware Setup:
 * - Connect one side of the potentiometer to GND
 * - The other side to 5V
 * - The middle pin (wiper) to analog pin A0
 */

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 bps
}

void loop() {
  int value = analogRead(A0);  // Read raw analog value (0–1023)
  Serial.print("Raw ADC value: ");
  Serial.println(value);

  // Convert raw value to voltage (in millivolts, then to volts)
  float voltage = map(value, 0, 1023, 0, 5000);  // 0–5V scaled to 0–5000 mV
  Serial.print("Voltage: ");
  Serial.print(voltage / 1000.0);  // Convert to volts
  Serial.println(" V");

  // Estimate resistance (assuming 10kΩ potentiometer)
  float resistor = map(value, 0, 1023, 0, 10000);  // Map to 0–10,000 ohms
  Serial.print("Estimated Resistance: ");
  Serial.print(resistor / 1000.0);  // Convert to kilo-ohms
  Serial.println(" kΩ");

  Serial.println();  // Empty line for spacing
  delay(300);        // Delay for readability
}
