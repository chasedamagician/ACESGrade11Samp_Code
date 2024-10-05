// PROJECT  :JoyStickPlotter
// PURPOSE  :Introduction to the Thumb Joystick (left, right, & PB) 
// COURSE   :ICS3U-E
// AUTHOR   :Class
// DATE     :2024 04 22
// MCU      :328P (Nano)
// STATUS   :Working
// REFERENCE:

// TJ
#define TJVERT A3
#define TJHORZ A2
#define SELECT 2
#define PACE 300

//Variables
volatile uint8_t triggered = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(SELECT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SELECT), ISR_Select, FALLING);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void ISR_Select() {
  triggered = true;
}

void loop() {
  if (triggered) {
    triggered = false;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  // Acquire readings
  uint16_t vertical = analogRead(TJVERT);
  uint16_t horizontal = analogRead(TJHORZ);
  
  // View on the Serial Plotter & Serial Monitor
  Serial.print("VERT:");
  Serial.print(vertical);
  Serial.print(',');
  Serial.print("HORZ:");
  Serial.println(horizontal);
  delay(PACE);
}