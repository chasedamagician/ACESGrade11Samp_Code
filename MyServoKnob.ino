// PROJECT  :MyServoKnob
// PURPOSE  :Strengthened version of the Servo | Knob example
// COURSE   :ICS3U
// AUTHOR   :C. D'Arcy
// DATE     :2024 05 10
// MCU      :328P
// STATUS   :Working
// REFERENCE:https://docs.arduino.cc/learn/electronics/servo-motors/
// REFERENCE:https://www.arduino.cc/reference/en/libraries/servo/

#include <Servo.h>  // Day 1: Library Use
Servo myServo;      // create servo object to control a servo

#define SPEED   15  // the angular rotation pace
#define POTGND  A0  // configure the potentiometer
#define POTPIN  A1  //
#define POTVCC  A2  //
#define SERVO   9   // Must use this pin to access Timer1
uint16_t reading;   // variable to store the value from the analog input

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(POTGND, OUTPUT);    // configure the potentiometer
  pinMode(POTVCC, OUTPUT);    //
  digitalWrite(POTGND, LOW);  //
  digitalWrite(POTVCC, HIGH); //
  myServo.attach(SERVO);      // attaches the servo on pin 9 to the servo object
}

void loop() {
  reading = analogRead(POTPIN);            // reads the value of the potentiometer (value between 0 and 1023)
  reading = map(reading, 0, 1023, 0, 180); // scale it for use with the servo (value between 0 and 180)
  myServo.write(reading);                  // sets the servo position according to the scaled value
  delay(SPEED);                            // permit servo to reach and hold the requested position
  Serial.print(myServo.read());            // echo the horn position
  Serial.println("°");
}
