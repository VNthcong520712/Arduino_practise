/* Vibration sensor module
   - Use 5V power supply
   - Connect analog output (AO) pin of the sensor to Arduino pin A0
*/

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A0);
  Serial.println(value);
  if (value > 415) {
    Serial.print("Vibrating ");
  } else {
    Serial.print("Not vibrating ");
  }
  delay(80);
}
