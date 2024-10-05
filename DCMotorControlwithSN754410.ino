// PROJECT  :DCMotorControlwithSN754410
// PURPOSE  :DC Hobby Motor (Sparkfun's ROB-11696) with SN75440 under control of 328P
// AUTHOR   :C. D'Arcy
// DATE     :2024 05 07
// uC       :328p (Nano)
// STATUS   :Working
// FRITZING :http://darcy.rsgc.on.ca/ACES/TEI3M/Fritzing/DCMotorControlSN754410.png
// INPUT #defines...
//#define INPUTSPEEDPIN   A1        //any digital pin would work for simply On/Off
#define INPUTSPEEDGND   A0        //potentiometer (as accelerator)
#define INPUTSPEEDPIN   A1        //potentiometer 
#define INPUTSPEEDVCC   A2        //potentiometer 
#define DIRECTIONVCC    9         //SPDT Slide Switch (as stick shift)
#define DIRECTIONPIN    10        //SPDT Slide Switch: 1-Forward; 0-Reverse
#define DIRECTIONGND    11        //SPDT Slide Switch
// OUTPUT #defines
#define OUTPUTSPEEDPIN  3         //PWM to SN754410: 3,4 ENABLE
#define MOTOR1TERMAPIN  4         //SN754410: 3A
#define MOTOR1TERMBPIN  5         //SN754410: 4A
#define MOTORSPEEDMAX   255       //
#define MOTOROFF        0         //
#define DURATION        3000      // dealy btween changing direction
uint8_t motorSpeed;
// efficient packaging of the state of the motor 
struct motorState {
  uint8_t termA;
  uint8_t termB;
};
// Four Standard Motor state definitions makes the coding tighter...
motorState mForward = {termA: HIGH, termB: LOW};
motorState mReverse = {termA: LOW, termB: HIGH};
motorState mBrake = {termA: HIGH, termB: HIGH}; // or both LOW
//motorState mCoast = {termA:?, termB:?};       //change IO pin direction to input?

uint8_t currentState;
uint8_t previousState;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(OUTPUTSPEEDPIN, OUTPUT);
  analogWrite(OUTPUTSPEEDPIN, MOTOROFF); // aka. digitalWrite(OUTPUTSPEEDPIN,LOW);
  //DIRECTION CONTROL: SPDT slide switch
  pinMode(DIRECTIONVCC, OUTPUT);
  pinMode(DIRECTIONGND, OUTPUT);
  digitalWrite(DIRECTIONVCC, HIGH);
  digitalWrite(DIRECTIONGND, LOW);
  // SPEED CONTROL: potentiometer(aka accelerator) input
  pinMode(INPUTSPEEDGND, OUTPUT);
  pinMode(INPUTSPEEDVCC, OUTPUT);
  digitalWrite(INPUTSPEEDGND, LOW);
  digitalWrite(INPUTSPEEDVCC, HIGH);

  // SN754410 H-BRIDGE pins
  pinMode(MOTOR1TERMAPIN, OUTPUT);
  pinMode(MOTOR1TERMBPIN, OUTPUT);
  currentState = digitalRead(DIRECTIONPIN);
  previousState = currentState;
  setState(currentState ? mForward : mReverse);
}

void setState(motorState state) {
  digitalWrite(MOTOR1TERMAPIN, state.termA);
  digitalWrite(MOTOR1TERMBPIN, state.termB);
}


void loop() {
  currentState = digitalRead(DIRECTIONPIN);
  if (currentState != previousState) {
    analogWrite(OUTPUTSPEEDPIN, MOTOROFF);
    delay(DURATION);
    setState(currentState ? mForward : mReverse);
    previousState = currentState;
  }
  motorSpeed = analogRead(INPUTSPEEDPIN) >> 2;
  Serial.print(currentState ? "Forward\t" : "Reverse\t");
  Serial.println(motorSpeed);
  analogWrite(OUTPUTSPEEDPIN, motorSpeed);   //convert [0,1023]->[0,255]->[0,9V]
}
