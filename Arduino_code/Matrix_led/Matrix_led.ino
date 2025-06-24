/*
  LED Matrix Display: Alphabet A to Z using 8x8 Matrix and 74HC595 Shift Register
  --------------------------------------------------------------------------------
  Description:
  This Arduino sketch displays characters from A to Z on an 8x8 LED matrix using a 74HC595 shift register.

  Wiring Instructions:
  --------------------
  - Connect 74HC595 to Arduino:
      * DS (Data)    -> Arduino pin 3
      * ST_CP (Latch)-> Arduino pin 4
      * SH_CP (Clock)-> Arduino pin 5

  - Connect LED matrix cathode rows (common ground) to Arduino pins:
      * Row 1 -> Pin 6
      * Row 2 -> Pin 7
      * ...
      * Row 8 -> Pin 13

  - Use current-limiting resistors (220Ω) on LED matrix columns or rows as needed.

  Display Notes:
  --------------
  - Each character is defined using 8 bytes (one byte per row).
  - Multiplexing is used to refresh the display rapidly and show each character clearly.
*/

int latchPin = 4;  // Latch pin for 74HC595
int clockPin = 5;  // Clock pin for 74HC595
int dataPin  = 3;  // Data pin for 74HC595

int pins[8] = {6, 7, 8, 9, 10, 11, 12, 13}; // LED row pins (cathode)

byte A[8] = {B00110000, B01001000, B10000100, B11111100, B10000100, B10000100, B10000100, B00000000};
byte B[8] = {B11110000, B10001000, B10001000, B11110000, B10001000, B10001000, B11110000, B00000000};
byte C[8] = {B00110000, B01001000, B10000000, B10000000, B10000000, B01001000, B00110000, B00000000};
byte D[8] = {B11100000, B10010000, B10001000, B10001000, B10001000, B10010000, B11100000, B00000000};
byte E[8] = {B11111000, B10000000, B10000000, B11111000, B10000000, B10000000, B11111000, B00000000};
byte F[8] = {B11111000, B10000000, B10000000, B11111000, B10000000, B10000000, B10000000, B00000000};
byte G[8] = {B00111000, B01000100, B10000000, B10000000, B10011100, B01000100, B00111000, B00000000};
byte H[8] = {B10001000, B10001000, B10001000, B11111000, B10001000, B10001000, B10001000, B00000000};
byte I[8] = {B11111000, B00100000, B00100000, B00100000, B00100000, B00100000, B11111000, B00000000};
byte J[8] = {B01111100, B00010000, B00010000, B00010000, B00010000, B10010000, B01100000, B00000000};
byte K[8] = {B10000100, B10001000, B10010000, B10100000, B11010000, B10001000, B10000100, B00000000};
byte L[8] = {B10000000, B10000000, B10000000, B10000000, B10000000, B10000000, B11110000, B00000000};
byte M[8] = {B10000010, B11000110, B10101010, B10010010, B10000010, B10000010, B10000010, B00000000};
byte N[8] = {B01000010, B01100010, B01010010, B01001010, B01000110, B01000010, B01000010, B00000000};
byte O[8] = {B00110000, B01001000, B10000100, B10000100, B10000100, B10000100, B01001000, B00110000};
byte P[8] = {B11110000, B10001000, B10001000, B11110000, B10000000, B10000000, B10000000, B00000000};
byte Q[8] = {B00110000, B01001000, B10000100, B10000100, B10000100, B10000100, B01001010, B00110001};
byte R[8] = {B11100000, B10010000, B10010000, B11100000, B10100000, B10010000, B10001000, B00000000};
byte S[8] = {B01110000, B10001000, B01000000, B00100000, B00010000, B00001000, B01000100, B00111000};
byte T[8] = {B11111000, B00100000, B00100000, B00100000, B00100000, B00100000, B00100000, B00000000};
byte U[8] = {B10001000, B10001000, B10001000, B10001000, B10001000, B10001000, B01110000, B00000000};
byte V[8] = {B10001000, B10001000, B10001000, B10001000, B01010000, B01010000, B00100000, B00000000};
byte W[8] = {B10000010, B10000010, B10000010, B10010010, B10101010, B11000110, B10000010, B00000000};
byte X[8] = {B10001000, B10001000, B01010000, B00100000, B01010000, B10001000, B10001000, B00000000};
byte Y[8] = {B10001000, B10001000, B01010000, B00100000, B00100000, B00100000, B00100000, B00000000};
byte Z[8] = {B11111000, B00001000, B00010000, B00100000, B01000000, B10000000, B11111000, B00000000};

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }
}

void loop() {
  display_characters();
}

// Display each character with ~1 second delay
void display_characters() {
  byte* letters[] = {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
  for (int i = 0; i < 26; i++) {
    for (int k = 0; k < 200; k++) {
      display_char(letters[i]);
    }
  }
}

// Multiplexing function to display a single character
void display_char(byte ch[8]) {
  for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, LOW);
    digitalWrite(pins[j], LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, ch[j]);
    digitalWrite(latchPin, HIGH);
    delay(1);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
    digitalWrite(latchPin, HIGH);
    digitalWrite(pins[j], HIGH);
  }
}
