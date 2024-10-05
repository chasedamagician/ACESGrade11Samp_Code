// PROJECT  :DCMotorControlwith5VRelay
// PURPOSE  :DC Hobby Motor (Sparkfun's ROB-11696) with 5V Relay under control of 328P
// AUTHOR   :C. D'Arcy
// DATE     :Confirmed. 2024 05 03. 2023 04 14. Updated from 2022 03 06 (3V Relay)
// uC       :328p (Nano)
// STATUS   :Working
// MOTOR    :(3-12V) https://www.sparkfun.com/products/11696
// RELAY    :https://www.amazon.ca/dp/B0874MC6D3?ref=ppx_yo2ov_dt_b_product_details&th=1
// PHOTO    :
// NOTES    :Demonstrates Forward, Reverse, and Coasting (Relay Power OFF)
#define OUTPUTSPEEDPIN  3         //PWM to MOSFET
#define RELAYCOIL       7         //2N3904 BJT controls direction (NC or NO)
#define DIRECTIONVCC    9         //Slide Switch (as stick shift)
#define DIRECTIONPIN    10        //1: Forward; 0: Reverse
#define DIRECTIONGND    11        //
#define INPUTSPEEDGND   A0        //potentiometer (as accelerator)
#define INPUTSPEEDPIN   A1        //potentiometer 
#define INPUTSPEEDVCC   A2        //potentiometer 
#define MOTORSPEEDMAX   255
#define MOTOROFF        0
#define DURATION        3000
uint8_t motorSpeed;

uint8_t direction;                //hold the active preference for motor rotation

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(OUTPUTSPEEDPIN, OUTPUT);
  analogWrite(OUTPUTSPEEDPIN, MOTOROFF); // aka. digitalWrite(OUTPUTSPEEDPIN,LOW);

  pinMode(RELAYCOIL, OUTPUT);
  digitalWrite(RELAYCOIL, HIGH);

  pinMode(DIRECTIONVCC, OUTPUT);
  pinMode(DIRECTIONGND, OUTPUT);
  digitalWrite(DIRECTIONVCC, HIGH);
  digitalWrite(DIRECTIONGND, LOW);

  pinMode(INPUTSPEEDGND, OUTPUT);
  pinMode(INPUTSPEEDVCC, OUTPUT);
  digitalWrite(INPUTSPEEDGND, LOW);
  digitalWrite(INPUTSPEEDVCC, HIGH);
}

void loop() {
    direction = digitalRead(DIRECTIONPIN);
    digitalWrite(RELAYCOIL, direction);
    motorSpeed = analogRead(INPUTSPEEDPIN) >> 2;
    Serial.print(direction ? "Forward:\t" : "Reverse:\t");
    Serial.println(motorSpeed);
    analogWrite(OUTPUTSPEEDPIN, motorSpeed);   //convert [0,1023]->[0,255]->[0,5V]
}
