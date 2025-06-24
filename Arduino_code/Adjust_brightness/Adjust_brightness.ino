/*
  LED Brightness Control (Fading Effect)

  Description:
  - This program gradually increases and decreases the brightness of an LED
    using PWM (Pulse Width Modulation).
  - The brightness changes in steps and reverses direction when it reaches
    maximum or minimum.

  Wiring:
  - Connect the anode (+) of the LED to pin 6 (with a 220Ω resistor).
  - Connect the cathode (–) of the LED to GND.
*/

int led = 6;       // PWM pin connected to LED
int value = 0;     // Current brightness level (0–255)
int step = 15;     // Amount to increase or decrease brightness each time

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, value);     // Set brightness level
  value = value + step;        // Update brightness value

  // Reverse direction at limits
  if (value <= 0 || value >= 225) {
    step = -step;
  }

  delay(50);                   // Small delay for smooth fading
}
