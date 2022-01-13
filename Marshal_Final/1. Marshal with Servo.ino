#include <SharpIR.h>
#define SENSOR_SAMPLES 20
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
//#define ADJUSTMENT +10                     //Compensation for reading variance in cm

LiquidCrystal_I2C lcd(0x27,16,2);
Servo servoLeftTop,servoLeft,servoRightTop,servoRight; //Servo Declarations
int pos1 = 0, pos2 = 0, pos3 = 0, pos4 =0;   //Servo motor positions
float dL,dR,dC;                              //Sharp Distance Sensor
int SensorPin = 0;

//The sensor output pin is attached to the pin A0
SharpIR watchL( SharpIR::GP2Y0A02YK0F, A0 );
SharpIR watchC( SharpIR::GP2Y0A02YK0F, A1 );
SharpIR watchR( SharpIR::GP2Y0A02YK0F, A2 );

void setup()
{
  servoLeftTop.attach(5);                                 //Left Top Servo
  servoLeft.attach(4);                                    //Left Servo 
  servoRightTop.attach(3);                                //Right Top Servo   
  servoRight.attach(2);                                   //Right Servo
    
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Marshall Bot");
  Serial.begin( 9600 ); //Enable the serial comunication
  pinMode(LED_BUILTIN,OUTPUT);
 }

char buffer[80] = { 0 };

float getMeanDistance( SharpIR &sensor )               // Scan runway & report distances seen by the 3 sensors:
{
  float total = 0;
  for( int i = 0;  i < SENSOR_SAMPLES;  ++i )
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
//  show(buffer);
    
  if( dL >= 77 && dL <= 93 && dC >= 65 && dC <= 132 && dR >= 45 && dR <= 55 )
  {
    show("Face me ");
    // waiting for an aircrraft <face me>;
    moveArms(60,0,60,0);
    
  }
    
  else if( dL >= 114 && dL <= 115 && dC >= 30 && dC <= 60 && dR >= 51 && dR <= 52 )
  {
    show("Go ahead ");
    // straight & in the middle of the runway <go straight>;
    moveArms(90,0,0,0); 
  }
      
  else if( dL >= 58 && dL <= 60 && dC >= 32 && dC <= 66 && dR >= 26 && dR <= 38 )
  {
    show("Go Left ");
    // on the right side of the runway <go left>;
    moveArms(130,0,130,0);
    
  }
  else if( dL >= 26 && dL <= 36 && dC >= 36 && dC <= 58 && dR >= 51 && dR <= 65 )
  {
    show("Go Right ");
    // on the left side of the runway <go right>;
    moveArms(90,0,60,0);
  }
    
  else if( dL >= 108 && dL <= 115 && dC >= 25 && dC <= 28 && dR >= 42 && dR <= 49 )
  {
    show("Slow Down ");
    // approaching to a stop <slow down>;
    moveArms(90,0,0,0);
    
  }
  else if( dL >= 114 && dL <= 118 && dC >= 19 && dC <= 22 && dR >= 49 && dR <= 45 )
  {
    show("Stop ");
    // stoping an aircraft <stop>;
    
  }
//    else
//  {
//    show( buffer );
//  }
  
}

// 4 Servo Motor motion control
void moveArms( int leftTop,int left,int rightTop,int right)
{
  servoLeftTop.write( leftTop );
  servoLeft.write( left );
  servoRightTop.write( rightTop );
  servoRight.write( right );
  
}

//LCD Display
void show(String S) {
  lcd.setCursor(0,1);
  lcd.print(S);
}

//  snprintf( buffer, 80, "L: [%3d] C: [%3d] cR: [%3d]\n", dL, dC, dR );
//  Serial.println( buffer );
//}
