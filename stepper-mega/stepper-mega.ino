int STP = 4; 
int DIR = 3; 
int delay_time = 10;
int speedValue = 0; // Variable to store the received speed value

void setup() {
  pinMode(STP, OUTPUT); // STP pin as output
  pinMode(DIR, OUTPUT); // DIR pin as output
  digitalWrite(DIR, HIGH); // Initial direction
  Serial.begin(115200); // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) { // Check if there's data available to read
    String data = Serial.readStringUntil('\n'); // Read the incoming data until newline character
    if (data.startsWith("speed:")) { // Check if the received data starts with "speed:"
      data.remove(0, 6); // Remove the "speed:" prefix
      speedValue = data.toInt(); // Convert the remaining string to an integer
      Serial.print("Speed value received: ");
      Serial.println(speedValue); // Print the received speed value

      // Map the speed value to delay_ms
      int delay_ms = map(speedValue, 0, 30, 2000, 500);
      Serial.print("Delay set to: ");
      Serial.println(delay_ms); // Print the mapped delay value

      // Perform stepping with the calculated delay_ms
      for(int x = 0; x < 10000; x++) {
        digitalWrite(STP, HIGH); 
        delayMicroseconds(delay_ms); 
        digitalWrite(STP, LOW); 
        delayMicroseconds(delay_ms); 
        
        if (Serial.available() > 0) { // Check if new speed data is available
          break; // Exit the loop to apply the new speed immediately
        }
      }
    }
  }

  delay(delay_time); // One second delay
}
