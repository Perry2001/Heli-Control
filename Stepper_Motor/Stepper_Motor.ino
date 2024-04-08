#include <FirebaseESP8266.h>
#include "connection.h"

FirebaseData firebaseData;
int lastSpeedValue = -1; // Variable to store the last speed value, initialized to -1

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToFirebase();
}

void loop() {
  if (Firebase.getInt(firebaseData, "/controls/speed")) {
    if (firebaseData.dataType() == "int") {
      int speedValue = firebaseData.intData();
      if (speedValue != lastSpeedValue) { // Check if the speed value has changed
        Serial.print("speed:");
        Serial.println(speedValue);
        lastSpeedValue = speedValue; // Update the last speed value
      }
    } else {
      Serial.println("Error: Speed value is not an integer");
    }
  } else {
    Serial.print("Failed to fetch speed value from Firebase: ");
    Serial.println(firebaseData.errorReason());
  }
  delay(1000); // Wait for 1 second before fetching again
}
