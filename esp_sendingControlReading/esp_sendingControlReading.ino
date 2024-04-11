#include "FirebaseESP8266.h"
#include "connection.h"

FirebaseData firebaseData;
int prevYValue = 0;
int prevSliderValue = 0;

void setup() {
  Serial.begin(115200);

  connectToWiFi();
  connectToFirebase();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');

    // Extract Y value
    int yIndex = data.indexOf("Y=") + 2;
    int yValue = data.substring(yIndex, data.indexOf('\t', yIndex)).toInt();
    // Map Y value from 0-1023 to 0-180
    int mappedYValue = map(yValue, 0, 1023, 20, 150);

    // Extract Slider value
    int sliderIndex = data.indexOf("S=") + 2;
    int sliderValue = data.substring(sliderIndex).toInt();
    // Map Slider value from 0-225 to 0-30
    int mappedSliderValue = map(sliderValue, 0, 225, 0, 30);

    // Check if data is different from previous data
    if (mappedYValue != prevYValue || mappedSliderValue != prevSliderValue) {
      // Update previous values
      prevYValue = mappedYValue;
      prevSliderValue = mappedSliderValue;

      // Send data to Firebase
      if (Firebase.setInt(firebaseData, "/controls/servo", mappedYValue)) {
        Serial.println("Y Value sent to Firebase");
      } else {
        Serial.println("Failed to send Y Value to Firebase");
        Serial.println(firebaseData.errorReason());
      }

      if (Firebase.setInt(firebaseData, "/controls/speed", mappedSliderValue)) {
        Serial.println("Slider Value sent to Firebase");
      } else {
        Serial.println("Failed to send Slider Value to Firebase");
        Serial.println(firebaseData.errorReason());
      }
    } else {
      Serial.println("Data not uploaded as it's same as previous data");
    }
  }
}
