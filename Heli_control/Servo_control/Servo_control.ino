#include <Servo.h>
#include <FirebaseESP8266.h>
#include "connection.h"

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToFirebase();

  servo1.attach(D1); // Modify pin numbers according to your setup
  servo2.attach(D2);
  servo3.attach(D3);
  servo4.attach(D4);
}

void loop() {
  if (Firebase.getInt(firebaseData, "/controls/servo")) {
    int servoValue = firebaseData.intData();
    servo1.write(servoValue);
    servo2.write(servoValue);
    servo3.write(servoValue);
    servo4.write(servoValue);
    Serial.print("Servo angle set to: ");
    Serial.println(servoValue);
  } else {
    Serial.println("Failed to fetch servo value from Firebase");
    Serial.println(firebaseData.errorReason());
  }
}
