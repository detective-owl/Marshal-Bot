#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define RCV_LED 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
RF24 radio(7, 8);                            //CNS,CE

const byte address[6] = "00001";

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, 00001);
  radio.startListening();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Marshall Bot");
  Serial.begin( 9600 ); //Enable the serial comunication
  pinMode(LED_BUILTIN, OUTPUT);
  
}


void loop()
{
  char dataStr[50];
  if (radio.available())
  {
    radio.read( &dataStr, sizeof(dataStr));
    digitalWrite( RCV_LED, HIGH );
    lcd.setCursor(0, 1);
    lcd.print(dataStr);
    Serial.println( dataStr );
    delay( 1000 ); //to give you time to see the message.
    digitalWrite( RCV_LED, LOW );
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Radio Unavailable");
    //lcd.clear();
  }
}


//LCD Display
void show(String S)
{
  lcd.setCursor(0, 1);
  lcd.print(S);
}
