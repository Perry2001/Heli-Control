const int STP = 4;
const int DIR = 3;

int delay_ms;

void setup() {
  Serial.begin(9600);
  pinMode(STP, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, HIGH);
}

void loop() {
  delay_ms = analogRead(A0); // Read analog input from A0

  // Constrain the delay_ms value to be within certain limits
  if (delay_ms > 1000) {
    delay_ms = 3000;
  } else if (delay_ms < 400 && delay_ms > 100) {
    delay_ms = 600;
  } else if (delay_ms < 100) {
    delay_ms = 300;
  }

  // digitalWrite(DIR, HIGH); // The motor moves in a particular direction
  // makes 100000 pulses
  digitalWrite(STP, HIGH);
  delayMicroseconds(delay_ms);
  digitalWrite(STP, LOW);
  delayMicroseconds(delay_ms);

  Serial.println(delay_ms);

  
}
