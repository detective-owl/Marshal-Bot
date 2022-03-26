#include <SPI.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  lcd.init();   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0, 0); //First line
  lcd.print("  Marshall Bot  ");
  delay(1000);
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    lcd.setCursor(0, 0);
    lcd.print("  Marshall Bot  ");
    lcd.setCursor(0, 1);
    lcd.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
