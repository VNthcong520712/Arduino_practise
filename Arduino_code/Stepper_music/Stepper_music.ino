/*
  Musical Notes with Stepper Motor using Adafruit Motor Shield
  -------------------------------------------------------------
  Description:
  This sketch plays a simple melody using a stepper motor connected to the
  Adafruit Motor Shield. The motor speed is varied to produce frequencies
  corresponding to musical notes. Each note is defined in an array, grouped
  by octave.

  Notes:
  ------
  - The motor is connected to port M3 and M4 (Motor 2 on the shield).
  - Frequencies used are approximations of musical notes.
  - Precision and sound quality depend on motor speed and step mode.
  - The motor steps in MICROSTEP mode, with approximately 200 steps/revolution.
  - This is a fun and experimental way to generate sound, not suitable for precise audio output.

  Hardware Requirements:
  ----------------------
  - Adafruit Motor Shield (v1 or v2)
  - Bipolar stepper motor (e.g. 28BYJ-48 or NEMA17)
  - External power supply for motor recommended

  Libraries Required:
  -------------------
  - AFMotor.h (Adafruit Motor Shield library)

  Musical Mapping:
  ----------------
  - The `music[]` array holds note indexes to play from note3[] (octave 3).
  - Index 7 is used as a rest note (pause).

*/

#include <AFMotor.h>

// Connect stepper motor to M3 and M4 (Motor 2)
AF_Stepper motor(200, 2); // 200 steps per revolution

// Define frequencies of notes (C, D, E, F, G, A, B) from octave 0 to 8
int note0[7] = {16.35, 18.35, 20.6, 21.83, 24.5, 27.5, 30.87};
int note1[7] = {32.7, 36.71, 41.2, 43.65, 49, 55, 61.74};
int note2[7] = {65.41, 73.42, 82.41, 87.31, 98, 110, 123.5};
int note3[7] = {130.8, 146.8, 164.8, 174.6, 196, 220, 246.9};
int note4[7] = {261.6, 293.7, 329.6, 349.2, 392, 440, 493.9};
int note5[7] = {523.3, 587.3, 659.3, 698.5, 784, 880, 987.8};
int note6[7] = {1047, 1175, 1319, 1397, 1568, 1760, 1976};
int note7[7] = {2093, 2349, 2637, 2794, 3136, 3520, 3951};
int note8[7] = {4186, 4699, 5274, 5588, 6272, 7040, 1902};

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Music Test");
}

void loop() {
  int stepsPerNote = 110;

  // Melody encoded using note indices (7 means rest)
  int music[] = {
    0, 0, 1, 0, 3, 2, 7, 
    0, 0, 1, 0, 4, 3, 7, 
    0, 0, 6, 5, 3, 2, 1, 
    7, 6, 6, 4, 2, 3, 2
  };

  Serial.println("Playing melody with MICROSTEPs...");

  for (int i = 0; i < sizeof(music) / sizeof(int); i++) {
    if (music[i] == 7) {
      Serial.println("----- Pause -----");
      delay(150);  // rest
    } else {
      motor.setSpeed(note3[music[i]]);                  // Set motor speed to note frequency
      motor.step(stepsPerNote, FORWARD, MICROSTEP);     // Step in microstepping mode
      delay(50);
    }
  }

  delay(1000); // Wait before repeating
}
