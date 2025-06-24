/* Connect Arduino to HC595 IC according to the following diagram
------IC Pin Number------------ARDUINO--------LED (LEDs share common anode, power -> 220Ω resistor -> common LED pins)
        15, 1-7                  X         LED 1-8    
           8                    GND
           9          (connected to pin 3 of another IC)
          10                    5V
          11                    D7
          12                    D6
          13                   GND          
          14                    D5
          16                    5V
*/

#define _clock 7
#define _latch 6
#define _data 5

void setup() {
  pinMode(_latch, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_data, OUTPUT);
}

void loop() {
  for (int i = 0; i < 256; i++)
  {
    digitalWrite(_latch, LOW);
    shiftOut(_data, _clock, LSBFIRST, i);
    digitalWrite(_latch, HIGH);
    delay(500);
  }
}   
