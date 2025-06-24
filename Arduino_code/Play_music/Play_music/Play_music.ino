/*
  SD Card Audio Player using TMRpcm Library
  -----------------------------------------
  Description:
  This sketch plays WAV audio files from an SD card using the TMRpcm library.
  It also allows basic playback control via the Serial Monitor.

  Features:
  ---------
  - Plays WAV files (8-bit, mono, 32kHz max) from SD card.
  - Allows control over playback via Serial input:
      'd' - Play "music.wav"
      'P' - Play "temple.wav"
      't' - Play "catfish.wav"
      'p' - Pause playback
      'S' - Stop playback
      '?' - Check if audio is playing
      '=' - Set volume to 1
      '-' - Set volume to 0 (mute)
      '0' - Set low audio quality
      '1' - Set high audio quality

  Wiring:
  -------
  - SD card module CS (Chip Select) -> Digital pin 4 (adjustable via SD_ChipSelectPin)
  - Speaker connected to pin 9 (or 5, 6, 11, 46 depending on board)

  Required Libraries:
  -------------------
  - SD
  - SPI
  - TMRpcm by TMRh20

  Notes:
  ------
  - Audio files must be in .wav format, 8-bit mono, ideally ≤ 32000 Hz.
  - Place WAV files in the root directory of the SD card.
*/

#include <SD.h>            // SD card library
#include <TMRpcm.h>        // Audio playback library
#include <SPI.h>           // SPI communication library

#define SD_ChipSelectPin 4 // SD card CS pin (change to 10/53 if needed)

TMRpcm tmrpcm;             // Create TMRpcm object
unsigned long time = 0;    // Timer for LED blinking

void setup() {
  tmrpcm.speakerPin = 9;   // Output pin for speaker (pin 9 for Uno/Nano)

  Serial.begin(9600);
  pinMode(13, OUTPUT);     // Onboard LED for blinking status

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");  // SD card not found or not initialized
    return;
  } else {
    Serial.println("SD ok");    // SD card ready
  }

  // Play file automatically at startup
  tmrpcm.play("Tieng-coi-xe-canh-sat-www_nhacchuongvui_com.wav");
}

void loop() {
  // Blink LED faster while playing, slower when idle
  if (tmrpcm.isPlaying() && millis() - time > 50) {
    digitalWrite(13, !digitalRead(13));
    time = millis();
  } else if (millis() - time > 500) {
    digitalWrite(13, !digitalRead(13));
    time = millis();
  }

  // Handle Serial commands for playback control
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'd': tmrpcm.play("music"); break;
      case 'P': tmrpcm.play("temple"); break;
      case 't': tmrpcm.play("catfish"); break;
      case 'p': tmrpcm.pause(); break;
      case '?':
        if (tmrpcm.isPlaying()) {
          Serial.println("A wav file is being played");
        }
        break;
      case 'S': tmrpcm.stopPlayback(); break;
      case '=': tmrpcm.volume(1); break;
      case '-': tmrpcm.volume(0); break;
      case '0': tmrpcm.quality(0); break;
      case '1': tmrpcm.quality(1); break;
      default: break;
    }
  }
}
