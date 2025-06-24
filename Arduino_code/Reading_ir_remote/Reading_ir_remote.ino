/*
 * IR Remote Control Reader using Arduino
 * ---------------------------------------
 * This program reads signals from an infrared (IR) remote using the IRremote library.
 * It decodes the IR signal and matches it to a list of known commands.
 * The corresponding command name is printed via the Serial Monitor.
 *
 * Hardware Setup:
 * - Connect the IR receiver module's OUT pin to digital pin 8
 * - VCC to 5V
 * - GND to GND
 *
 * Library Required:
 * - Install "IRremote" library via Arduino Library Manager
 */

#include <IRremote.h>

String charac;                  // Holds the decoded button label
const int receiverPin = 8;      // IR receiver connected to pin D8
IRrecv irrecv(receiverPin);     // IR receiver object
decode_results results;         // Stores decoded IR results

void setup() {
  Serial.begin(9600);           // Initialize serial communication
  irrecv.enableIRIn();          // Start the IR receiver
}

void loop() {
  // Check if a signal has been received
  if (irrecv.decode(&results)) {
    valuetochar();              // Convert the decoded value to a label
    Serial.print(results.value, HEX);  // Print raw hex value
    Serial.print("   ");
    Serial.println(charac);     // Print interpreted label
    delay(250);                 // Small delay to avoid repeated reads
    irrecv.resume();            // Receive the next signal
  }
}

// Match received IR value to corresponding label
void valuetochar() {
  String char_con[] = {
    "CH+", "CH", "CH-", "PREV", "NEXT", "PLAY/PAUSE",
    "-", "+", "EQ", "0", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "100+", "200+", "UNKNOWN COMMAND"
  };

  long dec_value[] = {
    16753245, 16736925, 16769565, 16720605, 16712445,
    16761405, 16769055, 16754775, 16748655, 16738455,
    16724175, 16718055, 16743045, 16716015, 16726215,
    16734885, 16728765, 16730805, 16732845, 16750695,
    16756815, 4294967295
  };

  // Loop through known values to find a match
  charac = "UNKNOWN COMMAND";  // Default value
  for (int i = 0; i < 22; i++) {
    if (results.value == dec_value[i]) {
      charac = char_con[i];
      break;
    }
  }
}
