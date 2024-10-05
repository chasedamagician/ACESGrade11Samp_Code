// PROJECT  :RotaryEncoderNanoPlotter
// PURPOSE  :Echoes CLK and DT (A and B) as a square wave on the Serial Plotter/Monitor
// COURSE   :*
// AUTHOR   :C. D'Arcy
// DATE     :2022 01 31. Confirmed 2024 04 01.
// MCU      :328P
// STATUS   :Working
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI4M/2021/images/RotaryEncoderSquare.png

#define INT0Pin 2         // A 
#define INT1Pin 3         // B
volatile uint8_t pinA;    //not PINA
volatile uint8_t pinB;    //not PINB
volatile uint8_t state;
volatile boolean triggered = false;
#define RUNLENGTH 20

void setup() {
  Serial.begin(9600);
  while (!Serial);
  attachInterrupt(digitalPinToInterrupt(INT0Pin), readEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INT1Pin), readEncoderB, CHANGE);
  Serial.print("CLK(A):");
  Serial.print(',');
  Serial.println("DT(B):");

}
/*
  ISR(INT0_vect){
  }

  ISR(INT1_vect){
  }
*/

void readEncoderA() {
  triggered = true;
  pinA = digitalRead(INT0Pin);
  pinB = digitalRead(INT1Pin);
}

void readEncoderB() {
  triggered = true;
  pinA = digitalRead(INT0Pin);
  pinB = digitalRead(INT1Pin);
}

void loop() {
  if (triggered) {
    triggered = false;
    displaySerial();
    //displayPlotter();
  }
}

void displaySerial() {
  Serial.print(pinA );
  Serial.print(',');
  Serial.println(pinB);
}

void displayPlotter() {
  for (uint8_t i = 0; i < RUNLENGTH; i++) {
    Serial.print(pinA ? 4 : 3);
    Serial.print(',');
    Serial.println(pinB ? 1 : 0);
  }
}
