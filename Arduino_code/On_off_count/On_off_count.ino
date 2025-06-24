/*
  Push Button Counter with LED Control

  Description:
  - This program counts how many times a button is pressed.
  - Every 4 presses, it turns an LED on; otherwise, the LED is off.
  - The result is printed to the Serial Monitor.

  Wiring Guide:
  - Use a push button, one 10KΩ resistor (pull-down), and one 220Ω resistor (for the LED).
  
  Button Wiring:
         ========   <- Push Button
         |      |
  5V ----        |----- 10KΩ resistor ----- GND
                |
                | (to Arduino digital pin 11)
                |
               OUT

  LED Wiring:
  - Connect the anode (+) of the LED to pin 2 (with a 220Ω resistor in series),
    and the cathode (–) to GND.
*/

const int buttonPin = 11;
const int ledPin = 2;

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect when button state changes
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("Button is being pressed");
      Serial.print("Press count: ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("Button released");
    }
  }

  lastButtonState = buttonState;

  // Every 4 presses, turn on the LED
  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED is ON");
  } else {
    digitalWrite(ledPin, LOW);
  }
}
