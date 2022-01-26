#include <SharpIR.h>
#define SENSOR_SAMPLES 20
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//#define ADJUSTMENT +10                     //Compensation for reading variance in cm

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoLeftTop, servoLeft, servoRightTop, servoRight; //Servo Declarations
int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;  //Servo motor positions
float dL, dR, dC;                            //Sharp Distance Sensor
int SensorPin = 0;
RF24 radio(7, 8);                            //CNS,CE

//The sensor output pin is attached to the pin A0
SharpIR watchL( SharpIR::GP2Y0A02YK0F, A0 );
SharpIR watchC( SharpIR::GP2Y0A02YK0F, A1 );
SharpIR watchR( SharpIR::GP2Y0A02YK0F, A2 );

const byte address[6] = "00001";

void setup()
{
  servoLeftTop.attach(5);                                 //Left Top Servo
  servoLeft.attach(4);                                    //Left Servo
  servoRightTop.attach(3);                                //Right Top Servo
  servoRight.attach(2);                                   //Right Servo

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Marshall Bot");
  Serial.begin( 9600 ); //Enable the serial comunication
  pinMode(LED_BUILTIN, OUTPUT);

  radio.begin();
  radio.openWritingPipe(00001);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

char buffer[80] = { 0 };

float getMeanDistance( SharpIR &sensor )               // Scan runway & report distances seen by the 3 sensors:
{
  float total = 0;
  for ( int i = 0;  i < SENSOR_SAMPLES;  ++i )
  {
    total += sensor.getDistance();
  }
  return total / SENSOR_SAMPLES;
}

void loop()
{
  int dL = getMeanDistance( watchL );
  int dC = getMeanDistance( watchC );
  int dR = getMeanDistance( watchR );
  snprintf( buffer, 80, "L:[%2d] C:[%2d] R:[%2d]\n", dL, dC, dR );
  Serial.println( buffer );
  //  show(buffer); //shows buffer in the LCD

  char myStr[50];
  //  strncpy( myStr, "Go Left", sizeof(myStr) );
  //  radio.write( &myStr, sizeof(myStr) );


  if ( dL >= 102 && dL <= 115 && dC >= 96 && dC <= 130 && dR >= 100 && dR <= 129 )
  {
    show("Face me ");
    strncpy( myStr, "Face me", sizeof(myStr) );
    radio.write( &myStr, sizeof(myStr) );

    // waiting for an aircrraft <face me>;
    moveArms(60, 0, 60, 0); //position where the marshall gesture should be
    delay(25); //delay for movement
    moveArms(60, 0, 60, 0); //neutral position

  }

  else if ( dL >= 64 && dL <= 81 && dC >= 61 && dC <= 84 && dR >= 56 && dR <= 68 )
  {
    show("Go ahead ");
    strncpy( myStr, "Go ahead", sizeof(myStr) );
    radio.write( &myStr, sizeof(myStr) );

    // straight & in the middle of the runway <go straight>;
    moveArms(0, 0, 170, 0); //position where the marshall gesture should be
    delay(40); //delay for movement
    moveArms(60, 0, 60, 0); //neutral position
  }

  else if ( dL >= 78 && dL <= 116 && dC >= 79 && dC <= 91 && dR >= 79 && dR <= 92 )
  {
    show("Go Left ");
    strncpy( myStr, "Go Left", sizeof(myStr) );
    radio.write( &myStr, sizeof(myStr) );

    // on the right side of the runway <go left>;
    moveArms(60, 0, 0, 0); //position where the marshall gesture should be
    delay(15); //delay for movement
    moveArms(0, 0, 0, 0); //neutral position

  }
  else if ( dL >= 118 && dL <= 121 && dC >= 83 && dC <= 85 && dR >= 76 && dR <= 86 )
  {
    show("Go Right ");
    strncpy( myStr, "Go Right", sizeof(myStr) );
    radio.write( &myStr, sizeof(myStr) );

    // on the left side of the runway <go right>;
    moveArms(180, 0, 0, 0); //position where the marshall gesture should be
    delay(40); //delay for movement
    moveArms(180, 0, 60, 0); //neutral position
  }

  //  else if( dL >= 41 && dL <= 43 && dC >= 28 && dC <= 34 && dR >= 30 && dR <= 33 )
  //  {
  //    show("Slow Down ");
  //    strncpy( myStr, "Slow Down", sizeof(myStr) );
  //  radio.write( &myStr, sizeof(myStr) );

  // approaching to a stop <slow down>;
  //      moveArms(0,0,0,0); //position where the marshall gesture should be
  //      delay(25); //delay for movement
  //      moveArms(0,0,0,0); //neutral position

  //  }
  else if ( dL >= 92 && dL <= 135 && dC >= 21 && dC <= 26 && dR >= 22 && dR <= 25 )
  {
    show("     Stop ");
    strncpy( myStr, "     Stop ", sizeof(myStr) );
    radio.write( &myStr, sizeof(myStr) );

    // stoping an aircraft <stop>;
    moveArms(45, 0, 75, 0); //position where the marshall gesture should be
    delay(25); //delay for movement
    moveArms(45, 0, 75, 0); //neutral position

  }
  //    else
  //  {
  //    show( buffer );
  //  }

}
void keepchecking()
{
  while (! ( dL >= 41 && dL <= 43 && dC >= 28 && dC <= 34 && dR >= 30 && dR <= 33 )) //must be in the stop me condition

  {
    loop();
  }
  //dL,dC,dR=checkallsensor(watchL, watchC, watchR); }
}

// 4 Servo Motor motion control
void moveArms( int leftTop, int left, int rightTop, int right)
{
  servoLeftTop.write( leftTop );
  servoLeft.write( left );
  servoRightTop.write( rightTop );
  servoRight.write( right );

}

//LCD Display
void show(String S) {
  lcd.setCursor(0, 1);
  lcd.print(S);
}

//  snprintf( buffer, 80, "L: [%3d] C: [%3d] cR: [%3d]\n", dL, dC, dR );
//  Serial.println( buffer );
//}
