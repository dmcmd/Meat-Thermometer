// include the library code:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

// named constants for the thermometer pins
const int meat1Pin = A1;
const int meat2Pin = A2;
const int meat3Pin = A3;
const int meat4Pin = A4;

// sensor value variables
int meat1Val = 0;
int meat2Val = 0;
int meat3Val = 0;
int meat4Val = 0;
int temp;

// set up probe detection variables
bool meat1ProbeDetect = 0;
bool meat2ProbeDetect = 0;
bool meat3ProbeDetect = 0;
bool meat4ProbeDetect = 0;

//variables to stop the screen from blinking
int prevMeat1F;
int prevMeat2F;
int prevMeat3F;
int prevMeat4F;

void setup() {

  // tell the arduino to use the AREF input pin to set the analog voltage reference to 3.3V
  analogReference(EXTERNAL);

  // Switch on the backlight
  lcd.backlight();

  // set up the number of columns and rows on the LCD
  lcd.init();
  lcd.clear();

  // set up temp pins
  pinMode(meat1Pin, INPUT);
  pinMode(meat2Pin, INPUT);
  pinMode(meat3Pin, INPUT);
  pinMode(meat4Pin, INPUT);

}

void loop() {

  // read the value on AnalogIn pins and store it

    meat1Val = analogRead(meat1Pin);
    meat2Val = analogRead(meat2Pin);
    meat3Val = analogRead(meat3Pin);
    meat4Val = analogRead(meat4Pin);

  // convert the meat probes to temperatures
  int meat1F = tempFunction(meat1Val);
  int meat2F = tempFunction(meat2Val);
  int meat3F = tempFunction(meat3Val);
  int meat4F = tempFunction(meat4Val);

  // set auto probe detection variables
  if (meat1F > -10) {
    meat1ProbeDetect = 1;
  }
  if (meat2F > -10) {
    meat2ProbeDetect = 1;
  }
  if (meat3F > -10) {
    meat3ProbeDetect = 1;
  }
  if (meat4F > -10) {
    meat4ProbeDetect = 1;
  }
  if (meat1F < -10) {
    meat1ProbeDetect = 0;
  }
  if (meat2F < -10) {
    meat2ProbeDetect = 0;
  }
  if (meat3F < -10) {
    meat3ProbeDetect = 0;
  }
  if (meat4F < -10) {
    meat4ProbeDetect = 0;
  }

  // print out temperatures on the screen
  lcd.setCursor(0, 0);
  lcd.print("Probe 1: ");
  if (meat1ProbeDetect == 0) {
    lcd.setCursor(9, 0);
    lcd.print("no probe");
  }
  if (meat1ProbeDetect == 1) {
    if (prevMeat1F != meat1F) {
      lcd.setCursor(9, 0);
      lcd.print("          ");
      lcd.setCursor(9, 0);
      lcd.print(meat1F);
      prevMeat1F = meat1F;
    }
  }
  lcd.setCursor(0, 1);
  lcd.print("Probe 2: ");
  if (meat2ProbeDetect == 0) {
    lcd.setCursor(9, 1);
    lcd.print("no probe");
  }
  if (meat2ProbeDetect == 1) {
    if (prevMeat2F != meat2F) {
      lcd.setCursor(9, 1);
      lcd.print("          ");
      lcd.setCursor(9, 1);
      lcd.print(meat2F);
      prevMeat2F = meat2F;
    }
  }
  lcd.setCursor(0, 2);
  lcd.print("Probe 3: ");
  if (meat3ProbeDetect == 0) {
    lcd.setCursor(9, 2);
    lcd.print("no probe");
  }
  if (meat3ProbeDetect == 1) {
    if (prevMeat3F != meat3F) {
      lcd.setCursor(9, 2);
      lcd.print("          ");
      lcd.setCursor(9, 2);
      lcd.print(meat3F);
      prevMeat3F = meat3F;
    }
  }
  lcd.setCursor(0, 3);
  lcd.print("Probe 4: ");
  if (meat4ProbeDetect == 0) {
    lcd.setCursor(9, 3);
    lcd.print("no probe");
  }
  if (meat4ProbeDetect == 1) {
    if (prevMeat4F != meat4F) {
      lcd.setCursor(9, 3);
      lcd.print("          ");
      lcd.setCursor(9, 3);
      lcd.print(meat4F);
      prevMeat4F = meat4F;
    }
  }
}

//calculate temperature of probe function
int tempFunction(int value) {
  int result;
  double RR, TT;
  RR = log((1 / ((1024 / (double)value) - 1)) * (double)22000);
  TT = (1 / ((0.7876984931E-3) + (2.069666861E-4) * RR + (1.202652917E-7) * RR * RR * RR)) - 273.25;
  result = ((int)((TT * 9.0) / 5.0 + 32.0));
  return result;
}
