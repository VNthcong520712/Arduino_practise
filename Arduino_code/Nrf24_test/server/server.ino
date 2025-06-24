/*
  NRF24L01 Wireless Server - Arduino Code
  ---------------------------------------
  Description:
  This Arduino sketch implements an NRF24L01 server that:
    - Sends a message to a client node (another NRF24L01 device)
    - Waits for a response from the client
    - Displays both sent and received messages on Serial Monitor

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
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE = pin 9, CSN = pin 8

const byte address[][6] = {"00011", "00022"};  // [0] = send to client, [1] = receive from client

void setup() {
  Serial.begin(115200);
  radio.begin();

  radio.openWritingPipe(address[0]);     // Transmit to client
  radio.openReadingPipe(1, address[1]);  // Receive from client
  radio.setPALevel(RF24_PA_MIN);         // Set power level
  radio.stopListening();                 // Start in transmit mode
}

void loop() {
  const char message[] = "Hello from server!";
  Serial.println("Sending message to client...");
  
  bool success = radio.write(&message, sizeof(message));

  if (success) {
    Serial.println("Message sent successfully.");

    // Wait for reply
    radio.startListening();  // Switch to receive mode
    unsigned long startTime = millis();
    bool timeout = false;

    while (!radio.available()) {
      if (millis() - startTime > 1000) { // 1-second timeout
        timeout = true;
        break;
      }
    }

    if (!timeout) {
      char reply[32] = "";
      radio.read(&reply, sizeof(reply));
      Serial.print("Received reply from client: ");
      Serial.println(reply);
    } else {
      Serial.println("No reply received from client.");
    }

    radio.stopListening();  // Back to transmit mode
    delay(1000);            // Wait before next send
  } else {
    Serial.println("Message failed to send.");
    delay(1000);
  }
}
