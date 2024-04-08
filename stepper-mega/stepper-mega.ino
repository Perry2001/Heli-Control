    /*
      e-Gizmo Microstep Driver Sample code


      *""""Wiring connections:"""*
       Gizduino MCU  to  Microstep
         D3  -------------> DIR
         D4  -------------> STP/CLK
         GND -------------> GND
         +5V -------------> VIN

      by e-Gizmo Mechatronix Central
      http://www.e-gizmo.com
      February 18, 2016

     */

  //Pin assignments
  int STP = 4; 
  int DIR = 3; 
  int delay_ms = 1000;
  int delay_time = 10;
    void setup() {
      //make the pins as an output
      pinMode(STP,OUTPUT); 
      pinMode(DIR,OUTPUT);
    }
    void loop() {
      // digitalWrite(DIR,HIGH); // The motor moves in a particular direction
      // makes 100000 pulses
      for(int x = 0; x < 10000; x++) {
        digitalWrite(STP,HIGH); 
        delayMicroseconds(delay_ms); 
        digitalWrite(STP,LOW); 
        delayMicroseconds(delay_ms); 
      }
      delay(delay_time); // One second delay
      
      digitalWrite(DIR,LOW); //Changes the direction
      // makes 10000 pulses
      for(int x = 0; x < 10000; x++) {
        digitalWrite(STP,HIGH);
        delayMicroseconds(delay_ms);
        digitalWrite(STP,LOW);
        delayMicroseconds(delay_ms);
      }
      delay(delay_time);
    }
