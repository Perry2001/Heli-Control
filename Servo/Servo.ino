#include "eGizmo_16channelServo.h"
#include <SoftwareSerial.h>

SoftwareSerial servoSerial(2, 3); // Software serial for servo controller
SoftwareSerial otherSerial(8, 9); // Software serial for communication with another Arduino

eGizmo_16channelServo servoDriver(&servoSerial);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  otherSerial.begin(9600); // Initialize other software serial communication
  servoDriver.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String value = Serial.readStringUntil('\n'); // Read integer value from otherSerial

    int position = value.toInt();

    if (position >= 10 && position <= 160) { // Ensure position is within valid range
      Serial.print("Moving all servos to position: ");
      Serial.println(position); // Print the position being moved to
      for (int i = 0; i < 16; i++) {
        servoDriver.moveServo(i, position);
      }
    } else {
      Serial.println("Invalid position. Position should be between 10 and 160 degrees.");
    }
  }

  delay(100); // Add a small delay to prevent reading too fast
}
