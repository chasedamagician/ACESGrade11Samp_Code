// PROJECT  :Timer1NormalMode0Blink
// PURPOSE  :Gentle introduction to AVR Timers. Sets up SERVO PWM (Mode 14)
// COURSE   :ICS3U
// AUTHOR   :C. D'Arcy
// DATE     :2024 05 11
// MCU      :328P
// STATUS   :Working
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/RegisterLevelServoPWM.docx

void setup() {
  //  pinMode(LED_BUILTIN, OUTPUT);
  DDRB |= (1 << PB5);   // pinMode(13,OUTPUT);

  // Register level...
  cli();      //NoInterrupts();
  
  // Normal Mode
  TCCR1A = 0;
  // set up timer with CLKio/256 prescaler
  TCCR1B = 1<<CS12; 
  // Enable Timer1 interrupt ability
  TIMSK1 = 1 << TOIE1;
  
  // Enable global interrupt ability...
  sei();      //Interrupts();
}

// Timer 1 Interrupt Service Routine
ISR(TIMER1_OVF_vect) {
  PORTB ^= (1 << PB5);    //toggle state of pin 13
}

void loop() {}   //nothing to do...