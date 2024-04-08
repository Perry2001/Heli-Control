#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "le3dp_rptparser2.0.h"
#include <SPI.h>

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);

// Variables to store previous joystick values
int prevYval = -1;
int prevSlider = -1;

void setup()
{
  Serial.begin( 115200 );
  
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  Serial.println("Start");
  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");
  delay( 200 );

  if (!Hid.SetReportParser(0, &Joy))
      ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );
}

void loop()
{
  int Xval;   // 0 - 1023
  int Yval;   // 0 - 1023
  int Hat;    // 0 - 15;
  int Twist;  // 0 - 255
  int Slider; // 0 - 255
  int Button; // 0 - 12 (0 = No button)
  
  Usb.Task();   
  JoyEvents.GetValues(Xval, Yval, Hat, Twist, Slider, Button);   //Copies joystick values to user

  if (Yval != prevYval || Slider != prevSlider) { // Check if values have changed
    Serial.print("Y=");
    Serial.print(Yval);
    Serial.print("\tS=");
    Serial.println(Slider);
    prevYval = Yval; // Update previous values
    prevSlider = Slider;
  }

  delay(100);
}
