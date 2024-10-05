// PROJECT  :RotaryEncoderAutoScroll
// PURPOSE  :Simulates auto scrolling of filenames on an LCD (preparing for Rotary Encoder)
// DEVICE   :Arduino + (Adafruit 1447) LCD Appliance
// AUTHOR   :C. D'Arcy (with Max and Rohan input)
// DATE     :2024 03 28
// uC       :328p (Nano)
// COURSE   :ICS3U
// STATUS   :Working
// REFERENCE:https://www.arduino.cc/en/Reference/LiquidCrystal
// REFERENCE:"Hello, World!" Tutorial: https://www.arduino.cc/en/Tutorial/HelloWorld
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/2223/images/LCDAnalogMeter2223.png
// REFERENCE:https://www.pjrc.com/teensy/td_libs_TimerOne.html
#include <TimerOne.h>             //support for autoscrolling
#include <LiquidCrystal.h>        //LCD Library...
#define LCD_COLUMNS 16            //Number of columns in Character LCD screen
#define LCD_ROWS    2             //Number of rows on LCD screen

//Pin assignments below are LCD Appliance-compatible
uint8_t EN = 9, RS = 8, D4 = 7, D5 = 6, D6 = 5, D7 = 4;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
#define INTERVAL 500000           // uS

// example of file names that could be read from an SD card...
String files[] = {
  "ArabzadehA.gcode",
  "ArabzadehC.gcode",
  "Bizzarri.gcode",
  "Cooper.gcode",
  "Gunasegaran.gcode",
  "Haick.gcode",
  "Hattrick.gcode",
  "Jamal.gcode",
  "Kafka.gcode",
  "Khare.gcode",
  "Li.gcode",
  "Ling.gcode",
  "Quintas-Tang.gcode",
  "Staznik.gcode",
  "Thompson.gcode",
  "Tiplady.gcode",
  "Zischka.gcode"
};

volatile uint8_t numFiles = 17;       //variables used in an ISR should
volatile boolean triggered = false;   //have the voltaile keyord applied to them 
volatile int8_t delta = 1;            //increment (1) or decrement (-1)
uint8_t cursor = 0;                   //index of the current file

void setup() {
  Serial.begin(9600);                 //just in case...
  while(!Serial);                     //wait to establish connection
  lcd.begin(LCD_COLUMNS, LCD_ROWS);   //initialize LCD screen
  updateDisplay(cursor);              //present the top of the list
  delay(500);                         //pause to give time to update LCD
  Timer1.initialize(INTERVAL);        //period between Timer1 interrupts
  Timer1.attachInterrupt(updateCursor); // scroll by one either way
}

void loop() {
  if (triggered) {                    //did a Timer1 interrupt occur?
    triggered = false;                // if so, prepare for the next one...
    updateDisplay(cursor);            //refresh the display...
  }
}
void updateCursor() {
  triggered = true;                   //Timer1 interrupt has occurred
  cursor += delta;                    //change the cursor
  if (cursor == 0 || cursor == numFiles - 2)  //did we reach the first or last element?
    delta = -delta;                   // if so, turn around
}

void updateDisplay(uint8_t c) {
  lcd.clear();                      //erase the LCD screen
  lcd.setCursor(0, 0);              //position display cursor at home
  lcd.print(files[c]);              //provide an instruction on the first line
  lcd.setCursor(0, 1);              //position display cursor at home
  lcd.print(files[c + 1]);          //provide an instruction on the first line
}
