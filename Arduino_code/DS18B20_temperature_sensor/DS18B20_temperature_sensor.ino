/* DS18B20 temperature sensor, 4.7K pull-up resistor
   - Pin 1: GND
   - Pin 2: Signal (connects to digital pin 2 and pull-up resistor to 5V)
   - Pin 3: 5V
*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() { 
  sensors.requestTemperatures();  
  Serial.print("Temperature: ");
  Serial.println(sensors.getTempCByIndex(0)); 
  delay(1000);
}
