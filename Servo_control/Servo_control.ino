#include <Servo.h>
#include <FirebaseESP8266.h>
#include "connection.h"

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

FirebaseData firebaseData;
int prevServoValue = -1; // Variable to store the previous servo value, initialized to -1

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToFirebase();

  servo1.attach(D3); // Modify pin numbers according to your setup
  servo2.attach(D4);
  servo3.attach(D5);
  servo4.attach(D6);
}

void loop() {
  if (Firebase.getInt(firebaseData, "/controls/servo")) {
    int servoValue = firebaseData.intData();
    if (servoValue != prevServoValue) { // Check if the servo value has changed
      int reversedServoValue = 180 - servoValue; // Reverse the servo value
      servo1.write(reversedServoValue);
      servo2.write(reversedServoValue);
      servo3.write(reversedServoValue);
      servo4.write(reversedServoValue);
      Serial.print("Servo angle set to: ");
      Serial.println(reversedServoValue);
      prevServoValue = servoValue; // Update the previous servo value
    }
  } else {
    Serial.println("Failed to fetch servo value from Firebase");
    Serial.println(firebaseData.errorReason());
  }
}
