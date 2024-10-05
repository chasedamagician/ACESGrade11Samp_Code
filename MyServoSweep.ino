// PROJECT  :MyServoSweep
// PURPOSE  :Strengthened version of the Servo | Sweep example
// COURSE   :ICS3U
// AUTHOR   :C. D'Arcy
// DATE     :2024 05 10
// MCU      :328P
// STATUS   :Working
// REFERENCE:https://docs.arduino.cc/learn/electronics/servo-motors/
// REFERENCE:https://www.arduino.cc/reference/en/libraries/servo/

#include <Servo.h>    // Day 1: Library
Servo myServo;        // create servo object to control a servo

#define SERVO   9     // control pin for the servo (Timer1)
#define SPEED   15    // the angular rotation pace 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  myServo.attach(SERVO);  // attaches the servo to pin 9 (Timer1) to the servo object
}

void loop() {
  // rotate from 0° to 180° in steps of 1°
  for (uint8_t pos = 0; pos <= 180; pos++) {
    myServo.write(pos);     // tell servo to go to position in variable 'pos'
    delay(SPEED);           // permit servo to reach and hold the requested position
    Serial.print(myServo.read());
    Serial.println("°");
  }
  // rotates from 180° to 0° in steps of 1°
  for (int16_t pos = 180; pos >= 0; pos--) {
    myServo.write(pos);     // tell servo to go to position in variable 'pos'
    delay(SPEED);           // permit servo to reach and hold the requested position
    Serial.print(myServo.read());
    Serial.println("°");
  }
}