/*
  Displaying Digits 0–9 on a Single 7-Segment LED via 74HC595 Shift Register

  Overview:
  - The 74HC595 is used to control a common-anode 7-segment LED.
  - The segments behave like 8 individual LEDs.
  - A segment lights up when the corresponding bit is LOW (0).
  - Unused segment (DP or dot) is typically not connected.

  LED-to-IC Mapping (Common Anode LED):
  -----LED Pin------IC Pin-----
       1              4
       2              3
       3             5V
       4              2
       5              7
       6              6
       7              5
       8              X (not used)
       9              15
      10              1

  74HC595 IC to Arduino and LED Connections:
  --------IC Pin-----------Arduino Pin----------Description
           8                   GND              (Ground)
           9         Connected to pin 3 of another 74HC595 if chained
          10                   5V               (Vcc)
          11                  D12               (SH_CP / Clock Pin)
          12                  D8                (ST_CP / Latch Pin)
          13                  GND               (Output Enable, active LOW)
          14                  D11               (DS / Data Pin)
          16                   5V               (Vcc)
*/

int latchPin = 8;   // ST_CP of 74HC595 (latch pin)
int clockPin = 12;  // SH_CP of 74HC595 (clock pin)
int dataPin = 11;   // DS of 74HC595 (data input pin)

// Segment values for digits 0–9
// Each byte represents the segments A–G and DP
// Bit order: DP-G-F-E-D-C-B-A (bit 7 to bit 0)
// Common Anode: LOW (0) turns segment ON, HIGH (1) turns it OFF
const int Seg[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void setup() {
  // These pins MUST be set as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  static int point = 0;

  // Start shifting data to 74HC595
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, Seg[point]);  // Send digit pattern
  digitalWrite(latchPin, HIGH);  // Latch to output

  point = (point + 1) % 10;  // Cycle from 0 to 9
  delay(500);               // Wait 0.5 seconds between updates
}
