#include <SharpIR.h>
#define SENSOR_SAMPLES 20
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 9); // RX, TX

unsigned long previousMillis = 0;        // will store last time LED was updated

const long interval = 500;           // interval at which to blink (milliseconds)

unsigned long previousMillis_1 = 0;        // will store last time LED was updated

const long interval_1 = 1000;           // interval at which to blink (milliseconds)


LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoLeftTop, servoLeft, servoRightTop, servoRight; //Servo Declarations
int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;  //Servo motor positions
float dL, dR, dC;                            //Sharp Distance Sensor
int SensorPin = 0;
int min_dL = 0;
int max_dL = 0;
int min_dC = 0;
int max_dC = 0;
int min_dR = 0;
int max_dR = 0;
int dL_buf = 0;
int dC_buf = 0;
int dR_buf = 0;
//The sensor output pin is attached to the pin A0
SharpIR watchL( SharpIR::GP2Y0A02YK0F, A0 );
SharpIR watchC( SharpIR::GP2Y0A02YK0F, A1 );
SharpIR watchR( SharpIR::GP2Y0A02YK0F, A2 );

bool calibrate = 0;
bool faceme = 0;
bool goahead = 0;
bool goahead_flg = 0;
bool turnright = 0;
bool turnright_flg = 0;
bool turnrightmax = 0;
bool turnrightmax_flg = 0;
bool turnleft = 0;
bool turnleft_flg = 0;
bool turnleftmax = 0;
bool turnleftmax_flg = 0;
bool slowdown = 0;
bool slowdown_flg = 0;
bool stopped = 0;
bool stopped_flg = 0;

void setup() {
  Serial.begin( 9600 ); //Enable the serial comunication
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Communication Ready");
  servoLeftTop.attach(5);                                 //Left Top Servo
  servoLeft.attach(4);                                    //Left Servo
  servoRightTop.attach(3);                                //Right Top Servo
  servoRight.attach(2);                                   //Right Servo

  moveArms(90, 0, 90, 0); //neutral position
  delay(500);
  moveArms(0, 0, 180, 0); //neutral position
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Marshall Bot");


  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("System Ready!!! ");
  delay(1000);
}

char buffer[80] = { 0 };

float getMeanDistance( SharpIR &sensor ) {              // Scan runway & report distances seen by the 3 sensors:
  float total = 0;
  for ( int i = 0;  i < SENSOR_SAMPLES;  ++i ) {
    total += sensor.getDistance();
  }
  return total / SENSOR_SAMPLES;
}
void loop() {
  unsigned long currentMillis_1 = millis();

  if (currentMillis_1 - previousMillis_1 >= interval_1) {
    // save the last time you blinked
    previousMillis_1 = currentMillis_1;
    int dL = getMeanDistance( watchL );
    int dC = getMeanDistance( watchC );
    int dR = getMeanDistance( watchR );
    Serial.print("dL: "); Serial.println(dL);
    Serial.print("dC: "); Serial.println(dC);
    Serial.print("dR: "); Serial.println(dR);
    if (calibrate == 0) {
      calibrate = 1;
      min_dL = dL;
      max_dL = dL;
      min_dC = dC;
      max_dC = dC;
      min_dR = dR;
      max_dR = dR;
    }
    // calibrate
    if (min_dL > dL) {
      min_dL = dL;
    }
    if (max_dL < dL) {
      max_dL = dL;
    }
    if (min_dC > dC) {
      min_dC = dC;
    }
    if (max_dC < dC) {
      max_dC = dC;
    }
    if (min_dR > dR) {
      min_dR = dR;
    }
    if (max_dR < dR) {
      max_dR = dR;
    }
    Serial.print("min_dL: ");
    Serial.println(min_dL);
    Serial.print("max_dL: ");
    Serial.println(max_dL);
    Serial.print("min_dC: ");
    Serial.println(min_dC);
    Serial.print("max_dC: ");
    Serial.println(max_dC);
    Serial.print("min_dR: ");
    Serial.println(min_dR);
    Serial.print("max_dR: ");
    Serial.println(max_dR);
    lcd.setCursor(0, 0);
    lcd.print(dL);
    lcd.print(" ");
    lcd.print(dC);
    lcd.print(" ");
    lcd.print(dR);
    lcd.print(" ");

    snprintf( buffer, 80, "L:[%2d] C:[%2d] R:[%2d]\n", dL, dC, dR );
    Serial.println( buffer );
    if ((dL >= 47 && dL <= 69) && (dC >= 26 && dC <= 35) && (dR >= 43 && dR <= 55)) {
      mySerial.println("Slow Down       ");
      lcd.setCursor(0, 1);
      lcd.print("Slow Down       ");
      slowdown = 1;
    } else(slowdown = 0);
    if ((dL >= 32 && dL <= 43) && (dC >= 19 && dC <= 23) && (dR >= 33 && dR <= 41)) {
      mySerial.println("Stop            ");
      lcd.setCursor(0, 1);
      lcd.print("Stop            ");
      stopped = 1;
    } else (stopped = 0);
    if ((dL >= 58 && dL <= 150) && (dC >= 35 && dC <= 74) && (dR >= 54 && dR <= 93)) {
      mySerial.println("Go Ahead        ");
      lcd.setCursor(0, 1);
      lcd.print("Go Ahead        ");
      goahead = 1;
    } else(goahead = 0);
    if ((dL >= 45 && dL <= 150) && (dC >= 73 && dC <= 85) && (dR >= 78 && dR <= 106)) {
      mySerial.println("Face Me         ");
      lcd.setCursor(0, 1);
      lcd.print("Face Me         ");
      faceme = 1;
    } else(faceme = 0);
    if ((dL >= 46 && dL <= 51) && (dC >= 56 && dC <= 73) && (dR >= 58 && dR <= 137)) {
      mySerial.println("GO Right        ");
      lcd.setCursor(0, 1);
      lcd.print("GO Right        ");
      turnright = 1;
    } else (turnright = 0);
    if ((dL >= 42 && dL <= 151) && (dC >= 54 && dC <= 71) && (dR >= 44 && dR <= 47)) {
      mySerial.println("GO Left         ");
      lcd.setCursor(0, 1);
      lcd.print("GO Left         ");
      turnleft = 1;
    } else (turnleft = 0);
    if ((dL >= 61 && dL <= 151) && (dC >= 84 && dC <= 134) && (dR >= 76 && dR <= 151)) {
      mySerial.println("GO Max Right    ");
      lcd.setCursor(0, 1);
      lcd.print("GO Max Right    ");
      turnrightmax = 1;
    } else (turnrightmax = 0);
    if ((dL >= 56 && dL <= 151) && (dC >= 87 && dC <= 145) && (dR >= 66 && dR <= 80)) {
      mySerial.println("GO Max Left     ");
      lcd.setCursor(0, 1);
      lcd.print("GO Max Left     ");
      turnleftmax = 1;
    } else(turnleftmax = 0);
  }
  //delay(500);
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    if (faceme == 1) {
      Serial.println("Face Me");
      moveArms(90, 0, 90, 0); //position where the marshall gesture should be
    }
    if (goahead == 1) {
      Serial.println("Go Ahead");
      if (goahead_flg == 0) {
        goahead_flg = 1;
        moveArms(90, 0, 90, 0); //position where the marshall gesture should be
      } else {
        goahead_flg = 0;
        moveArms(0, 0, 180, 0); //neutral position
      }
    }
    if (turnright == 1) {
      Serial.println("Turn Right");
      if (turnright_flg == 0) {
        turnright_flg = 1;
        moveArms(90, 0, 90, 0); //position where the marshall gesture should be
      } else {
        turnright_flg = 0;
        moveArms(90, 0, 180, 0); //neutral position
      }
    }
    if (turnrightmax == 1) {
      Serial.println("Turn Right Max");
      if (turnrightmax_flg == 0) {
        turnrightmax_flg = 1;
        moveArms(90, 0, 90, 0); //position where the marshall gesture should be
      } else {
        turnrightmax_flg = 0;
        moveArms(90, 0, 180, 0); //neutral position
      }
    }
    //turn left
    if (turnleft == 1) {
      Serial.println("Turn Left");
      if (turnleft_flg == 0) {
        turnleft_flg = 1;
        moveArms(90, 0, 90, 0); //position where the marshall gesture should be
      } else {
        turnleft_flg = 0;
        moveArms(0, 0, 90, 0); //neutral position
      }
    }
    if (turnleftmax == 1) {
      Serial.println("Turn Left Max");
      if (turnleftmax_flg == 0) {
        turnleftmax_flg = 1;
        moveArms(90, 0, 90, 0); //position where the marshall gesture should be
      } else {
        turnleftmax_flg = 0;
        moveArms(0, 0, 90, 0);  //neutral position
      }
    }
    if (slowdown == 1) {
      Serial.println("Slow Down");
      if (slowdown_flg == 0) {
        slowdown_flg = 1;
        moveArms(90, 0, 90, 0); //position where the marshall gesture should be
      } else {
        slowdown_flg = 0;
        moveArms(180, 0, 0, 0); //neutral position
      }
    }
    if (stopped == 1) {
      Serial.println("Stop");
      moveArms(0, 0, 180, 0); //position where the marshall gesture should be
    }
  }
}

// 4 Servo Motor motion control
void moveArms( int leftTop, int left, int rightTop, int right)
{
  servoLeftTop.write( leftTop );
  servoLeft.write( left );
  servoRightTop.write( rightTop );
  servoRight.write( right );
}
