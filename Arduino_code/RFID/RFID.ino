/*
  RFID Access Control using MFRC522
  ----------------------------------
  Description:
  This sketch uses the MFRC522 RFID reader to detect and authenticate RFID cards by checking their UID.
  When a known card is scanned, access is granted. Unknown cards will be denied.
  A signal pin (pin 3) is toggled HIGH or LOW depending on the result.

  Wiring Diagram (MFRC522 to Arduino UNO/Nano):
  ---------------------------------------------
  RFID Module    | Arduino
  ---------------|--------
  MOSI           | D11
  MISO           | D12
  SCK            | D13
  SDA (SS)       | D10
  RST            | D9
  VCC (3.3V)     | 3.3V
  GND            | GND

  Notes:
  ------
  - Authorized UIDs must be added to the condition inside loop.
  - The current code grants access to cards with UID "6C 5A 06 32" or "7C 74 81 26".
  - Output pin D3 is turned LOW when access is granted or denied.
  - Use Serial Monitor (9600 baud) to view card UID and access status.

  Libraries Required:
  -------------------
  - SPI
  - MFRC522 by Miguel Balboa
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10      // Slave Select (SDA) pin
#define RST_PIN 9      // Reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void setup()
{
  pinMode(3, OUTPUT);         // Output control pin
  digitalWrite(3, HIGH);      // Default state HIGH
  Serial.begin(9600);         // Start serial communication
  SPI.begin();                // Start SPI bus
  mfrc522.PCD_Init();         // Initialize RFID module
  Serial.println("Place your RFID card near the reader...");
  Serial.println();
}

void loop()
{
  // Look for new RFID cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select the detected card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID tag : ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();  // Convert to uppercase

  // ------- Access control check -------
  if (content.substring(1) == "6C 5A 06 32" || content.substring(1) == "7C 74 81 26") {
    digitalWrite(3, LOW);
    Serial.println("Authorized access");
    Serial.println();
  } else {
    digitalWrite(3, LOW);
    Serial.println("Access denied");
    Serial.println();
  }
}
