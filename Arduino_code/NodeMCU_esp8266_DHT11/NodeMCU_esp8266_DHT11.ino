/*
  Temperature & Humidity Monitoring with Blynk + LED Control
  - This program uses a DHT11 sensor to read temperature and humidity values.
  - The values are sent to the Blynk app over WiFi.
  - A virtual LED (V0) is toggled every second as a status indicator.

  Wiring:
  - DHT11:
      + VCC -> 3.3V or 5V
      + GND -> GND
      + DATA -> D2 (GPIO2)
  - ESP8266 (e.g., NodeMCU or Wemos D1 mini) connects via WiFi.
  
  Notes:
  - Replace `***` with your actual Blynk Auth Token, WiFi SSID, and password.
  - Virtual pins:
      + V0: Virtual LED
      + V5: Humidity
      + V6: Temperature
*/

#include <SimpleTimer.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Blynk.h>

#define DHTPIN 2              // DHT11 connected to D2 (GPIO2)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;
WidgetLED led1(V0);

// Replace with your own Blynk Auth Token and WiFi credentials
char auth[] = "***************";   // Blynk Auth Token
char ssid[] = "***************";   // WiFi SSID
char pass[] = "***************";   // WiFi Password

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  // Toggle virtual LED
  if (led1.getValue()) {
    led1.off();
  } else {
    led1.on();
  }

  // Send humidity and temperature to Blynk
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
