#include <FirebaseESP8266.h>
#include <Stepper.h>
#include "connection.h"

#define STEPS_PER_REVOLUTION 200 // Modify this according to your stepper motor

const int stepsPerRevolution = STEPS_PER_REVOLUTION;
Stepper stepper(stepsPerRevolution, D1, D3, D2, D4); // Change pins according to your setup

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToFirebase();
  stepper.setSpeed(0); // Initial speed
}

void loop() {
  if (Firebase.getInt(firebaseData, "/controls/speed")) {
    int speedValue = firebaseData.intData();
    stepper.setSpeed(speedValue);
    Serial.print("Speed set to: ");
    Serial.println(speedValue);
  } else {
    Serial.println("Failed to fetch speed value from Firebase");
    Serial.println(firebaseData.errorReason());
  }
}
