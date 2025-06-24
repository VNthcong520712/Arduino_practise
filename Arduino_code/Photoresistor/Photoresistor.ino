/* For light-sensitive switch: requires LDR, 220Ω resistor, LED, 10K potentiometer, 10K resistor, 100nF capacitor (104)
    Middle pin of the potentiometer connects to A4
    Positive voltage goes to one pin of the LDR, LDR connects in series with a 10K resistor, resistor connects to ground
    104 capacitor connects between the junction of the LDR and resistor, and ground
    Pin D2 is used for output signal to LED
    The LDR signal is taken from the junction between the LDR and resistor
*/
int ldr = A5; 
int potentiometer = A4; 
int led = 2;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  int ldrValue = analogRead(ldr);
  int potValue = analogRead(potentiometer);
  
  // If LDR value <= potentiometer value, turn on the LED
  if (ldrValue <= potValue) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  // Print values to Serial Monitor
  Serial.print("LDR ");
  Serial.print(ldrValue);
  Serial.print(", Potentiometer ");
  Serial.print(potValue);
  Serial.print(" => ");
  Serial.println((ldrValue <= potValue) ? "On" : "Off"); 
}