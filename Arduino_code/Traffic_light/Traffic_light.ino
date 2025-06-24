/*
 * Simple Traffic Light LED Simulation
 * -----------------------------------
 * This program simulates a basic 3-color traffic light using LEDs.
 *
 * LED Connections:
 * - Green LED (Go)  → Digital pin 2
 * - Red LED (Stop)  → Digital pin 3
 * - Yellow LED (Wait) → Digital pin 4
 *
 * LEDs should be connected in series with resistors (~220Ω) to ground.
 * This simulates a typical traffic light timing cycle.
 */

int waitLed = 4;   // Yellow LED (Wait)
int stopLed = 3;   // Red LED (Stop)
int goLed = 2;     // Green LED (Go)

void setup() {
  pinMode(goLed, OUTPUT);
  pinMode(stopLed, OUTPUT);
  pinMode(waitLed, OUTPUT);
}

void loop() {
  // Turn off all lights briefly before each cycle
  digitalWrite(goLed, LOW);
  digitalWrite(stopLed, LOW);
  digitalWrite(waitLed, LOW);
  delay(1);

  // Yellow light on (prepare to stop)
  digitalWrite(waitLed, HIGH);
  delay(5000);              // Yellow light stays on for 5 seconds
  digitalWrite(waitLed, LOW);

  // Red light on (stop)
  digitalWrite(stopLed, HIGH);
  delay(20000);             // Red light stays on for 20 seconds
  digitalWrite(stopLed, LOW);

  // Green light on (go)
  digitalWrite(goLed, HIGH);
  delay(20000);             // Green light stays on for 20 seconds
  // Then cycle repeats
}
