// PROJECT  :Timer1FastPWMMode14
// PURPOSE  :Foundation for Servo PWM driving circuit
// COURSE   :ICS3U
// AUTHOR   :C. D'Arcy
// DATE     :2024 05 14
// MCU      :328P
// STATUS   :Working
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/RegisterLevelServoPWM.docx
// NOTES    :Frequency and duty cycle depend on Timer configuration
//          :Optimum thresholds vary with particular Servo
// Trial & Error on an FS5103B Servo from ABRA
#define LOWER 1200      // Lower bound for OCR1A: 0°
#define UPPER 4800      // Upper Bound for OCR1A: 180°
#define TOP 10 * UPPER  // ICR1 (Threshold for 50Hz servo waveform)

#define DEBUG  // Optional Serial Monitoring. Comment out if not required

// flags to signal interrupt occurences
volatile boolean OCR1AMatch = false;
volatile boolean ICR1Match = false;

int8_t delta = 100;  // influences the speed or the servo horn rotation

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  while (!Serial);
#endif
  //disable global interrupt system while configuring...
  cli();

  // Define OC1A (Arduino pin 9) for output
  DDRB |= (1 << PB1);  //aka pinMode(9, OUTPUT);

  // Configure OC1A pin to clear on Compare Match (non-inverting)
  //  and WGM parameters for Fast PWM Mode 14  (ICR1 as TOP)
  // NOTE: Do not use |= as the Arduino Toolchain sets some flags before this
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  // Set prescaler and further WGM parameters for Fast PWM Mode 14
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);  //CLKDIV8

  // Configure PWM characteristics
  ICR1 = TOP;     // Establish frequency of 50Hz (period of 20ms)
  OCR1A = LOWER;  // Duty cycle: 5%

  // Enable Output Compare Interrupt ability
  //TIMSK1 = 1 << OCIE1A;
  TIMSK1 = (1 << OCIE1A) | (1 << TOIE1);

  //reenable global interrupt system...
  sei();
}

// Timer1 Output Compare triggered on TCNT1 == OCR1A
ISR(TIMER1_COMPA_vect) {
  OCR1AMatch = true;
}

// Timer1 Overflow Output Compare triggered on TCNT1 == TOP (ICR1)
ISR(TIMER1_OVF_vect) {
  ICR1Match = true;
}
void loop() {
  if (OCR1AMatch) {      // did a Compare Match occur between TCNT1 and OCR1A?
    OCR1AMatch = false;  // if so, prepare to recognize the next one...
#ifdef DEBUG
    Serial.print("OCR1A Compare Match: ");  // say so, if necessary...
    Serial.print(OCR1A);
    Serial.print('\t');
#endif
    OCR1A += delta;                      // prepare to rotate the horn
    if (OCR1A < LOWER || OCR1A > UPPER)  //reverse direction if necessary...
      delta = -delta;
  }
  if (ICR1Match) {      // did an Overflow occur? TCNT1  == TOP (ICR1)?
    ICR1Match = false;  // if so, prepare to recognize the next one...
#ifdef DEBUG
    Serial.print("ICR1 Compare Match (Timer Overflow): ");  // say so, if necessary...
    Serial.println(ICR1);
#endif
  }
}