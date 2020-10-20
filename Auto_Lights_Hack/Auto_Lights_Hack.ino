#include <Adafruit_SoftServo.h>

#define SERVOPIN 0

Adafruit_SoftServo myServo1;

void setup() {
   // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)

  
  myServo1.attach(SERVOPIN);
  myServo1.write(90);
  delay(15);
  
}

void loop() {
  int servoPos1 = 0;  // variable to convert voltage on pot to servo position
  int servoPos2 = 180;  // variable to convert voltage on pot to servo position
  myServo1.write(servoPos1);                    // tell servo to go to position
  delay(1000);                              // waits 15ms for the servo to reach the position
  myServo1.write(servoPos2);
  delay(1000);
  myServo1.write(servoPos1);
  delay(900000);

}


// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
// The SIGNAL(TIMER0_COMPA_vect) function is the interrupt that will be
// Called by the microcontroller every 2 milliseconds
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
  }
}
