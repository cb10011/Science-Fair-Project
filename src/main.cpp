#include <Arduino.h>

/*
   DigitalReadSerial

   Reads a digital input on pin 2, prints the result to the Serial Monitor

   This example code is in the public domain.

   http://www.arduino.cc/en/Tutorial/DigitalReadSerial
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int  pushButton   = 2;
bool pushedBefore = false;
bool firstText    = false;
int  msTotal      = 0;
int  waitTime     = 500;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);

  if (buttonState == 0) {
    if (pushedBefore == true) {
      msTotal += waitTime;
    } else {
      msTotal = waitTime;
    }
    pushedBefore = true;
  }

  if ((buttonState == 0) && (msTotal >= 2000) && (msTotal < 2000 + waitTime)) {
    Serial.println("on");
  } else if ((buttonState == 1) && (msTotal >= 2000 and pushedBefore == true)) {
    Serial.println("off");
  }

  if (buttonState == 1) {
    msTotal      = 0;
    pushedBefore = false;
  }
  delay(waitTime);
}
