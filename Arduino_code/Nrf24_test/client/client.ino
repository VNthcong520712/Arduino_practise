/*
  NRF24L01 Wireless Client - Arduino Code
  ---------------------------------------
  Description:
  This Arduino sketch implements a simple NRF24L01 client that:
    - Receives a message from a remote transmitter (another NRF24L01 node)
    - Prints the received message to the Serial Monitor
    - Sends a reply message back to the transmitter

  Wiring:
  -------
  NRF24L01 | Arduino UNO
  ---------|--------------
  GND      | GND
  VCC      | 3.3V (NOT 5V!)
  CE       | D9
  CSN      | D8
  SCK      | D13
  MOSI     | D11
  MISO     | D12

  Libraries:
  ----------
  - SPI
  - nRF24L01
  - RF24 by TMRh20

  Note:
  -----
  - Make sure both devices use the same address pairing and data rate.
  - Address format must match (5-character strings).
*/

#include <SPI.h>  
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE = pin 9, CSN = pin 8

const byte address[][6] = {"00011", "00022"};  // [0] = receive, [1] = send

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1, address[0]);  // Set receive address
  radio.openWritingPipe(address[1]);     // Set transmit address
  radio.setPALevel(RF24_PA_MIN);         // Set power level to minimum (reduce noise/interference)
}

void loop() {
  // ===== Receive message from transmitter =====
  radio.startListening();

  if (radio.available()) { 
    Serial.println("Incoming message:");
    
    char text[32] = "";           // Buffer for incoming message
    radio.read(&text, sizeof(text));
    Serial.println(text);

    delay(20);                    // Short delay before sending response

    // ===== Send response back to transmitter =====
    radio.stopListening();        // Switch to transmit mode

    const char response[] = "Message received. Signal is good.";
    radio.write(&response, sizeof(response));
    
  } else {
    Serial.println("No connection. Waiting...");
  }
}
