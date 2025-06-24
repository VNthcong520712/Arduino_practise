/*
  LED Blinking Pattern with Timed Phases - "nhap.ino"
  ---------------------------------------------------
  Description:
  This Arduino sketch controls two LEDs (on pins 9 and 10) in a predefined blinking pattern based on time intervals.
  The pattern alternates the states of LED1 and LED2 using a timing sequence that mimics a Morse-code-like pulse.

  Functionality:
  -------------
  - LED1 and LED2 are turned ON/OFF following a complex sequence of time delays.
  - Each phase waits for a certain amount of milliseconds (e.g., 90ms, 270ms, etc.).
  - After completing the full sequence (~1.4s), the timer resets and repeats.
  - The current states of LED1 and LED2 are printed to the Serial Monitor for debugging.

  Pin Assignment:
  --------------
  - LED1 -> Pin 9
  - LED2 -> Pin 10

  Note:
  -----
  You can connect two LEDs with appropriate resistors to observe the pattern.
*/

byte led1 = 9;                      // LED1 connected to digital pin 9
byte led2 = 10;                     // LED2 connected to digital pin 10
unsigned long timedelay = 0;        // Stores the start time of each cycle

void setup()
{
  Serial.begin(9600);               // Initialize serial communication for debugging
  pinMode(led1, OUTPUT);            // Set pin 9 as output
  pinMode(led2, OUTPUT);            // Set pin 10 as output
  digitalWrite(led1, LOW);          // Turn off both LEDs initially
  digitalWrite(led2, LOW);
}

void loop()
{
  // Phase 1: After 90 ms, LED1 ON, LED2 OFF
  if ((unsigned long)(millis() - timedelay) >= 90) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);

    // Phase 2: After total 360 ms, both OFF
    if ((unsigned long)(millis() - timedelay) >= (270 + 90)) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);

      // Phase 3: After total 450 ms, LED1 ON, LED2 OFF
      if ((unsigned long)(millis() - timedelay) >= (90 + 90 + 270)) {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);

        // Phase 4: After total 990 ms, both OFF
        if ((unsigned long)(millis() - timedelay) >= (270 + 270 + 90 + 90)) {
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);

          // Phase 5: After total 1420 ms, LED2 ON, LED1 OFF
          if ((unsigned long)(millis() - timedelay) >= (90 + 90 + 90 + 270 + 270 + 80)) {
            digitalWrite(led2, HIGH);
            digitalWrite(led1, LOW);

            // Phase 6: After total 1690 ms, both OFF
            if ((unsigned long)(millis() - timedelay) >= (90 + 90 + 90 + 270 + 270 + 80 + 270)) {
              digitalWrite(led2, LOW);
              digitalWrite(led1, LOW);

              // Phase 7: After total 1780 ms, LED2 ON, LED1 OFF
              if ((unsigned long)(millis() - timedelay) >= (90 + 90 + 90 + 270 + 270 + 80 + 270 + 90)) {
                digitalWrite(led2, HIGH);
                digitalWrite(led1, LOW);

                // Phase 8: After total 2150 ms, both OFF and reset timer
                if ((unsigned long)(millis() - timedelay) >= (270 + 90 + 90 + 90 + 270 + 270 + 80 + 270 + 90)) {
                  digitalWrite(led2, LOW);
                  digitalWrite(led1, LOW);
                  timedelay = millis(); // Reset timer to start the sequence again
                }
              }
            }
          }
        }
      }
    }
  }

  // Print current LED states to Serial Monitor
  Serial.print(digitalRead(led1));
  Serial.print("            ");
  Serial.println(digitalRead(led2));
}
