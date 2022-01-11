# Marshal-Bot
Automated Aircraft Marshaling System with wireless display
I used the original code of HenryChu in this project but encountered some issues with it. I am trying to learn how to integrate the NRF24L01 in this system to add another wireless display.

Here is the demostration that HenryChu made (https://www.youtube.com/watch?v=_LAO7Xp4yGY&ab_channel=HenryChu). I'm trying to do this type of signals so for now, I'll only be using 2 of the servo (https://www.youtube.com/watch?v=0Mpl4VtUABI&ab_channel=MABTechnicalTraining).

##THINGS TO DO OR ISSUES:
I still don't know how to make the servo move in a repeated gesture.
How to integrate the NRF24L01 for a secondary wireless display.

##NOTE:
Left Top and Right top refers to the servo facing the actual plane not the one connecting to the other servo.
Left and Right IR must be pointed at the end of the wings of the aircraft and the Center IR must be directly pointed in the nose of the aircraft.
Make sure your surface is completly flat and is non reflective. This is to minimize any noise within the projecct.

##PROBLEMS ENCOUNTERED:
Sharp Infrared sensor is not accurate and is only consistent in specific ranges not the whole range specified in the data sheet. Putting a 200uF capacitor between the IR sensors stabilizes some of the values. Meaning you should find the working range of the IR sensor for it to be usable. The IR sensors should also not be positioned near to one another as this gives out some interference.
When finding a usable range get 5 values and average them out.

##PROGRESS:
https://streamable.com/qh4wsc
MATERIALS USED:
3 Sharp IR Sensor GP2Y0A02YK0F
4 SG90 Servo Motor
2 Arduino Uno
IC2 LCD Display

##ARDUINO CONNECTIONS:
LCD

GND-GND
VCC-VCC
SDA-A4
SCK-A5
Servo Motors 1 (Left Top)

Brown-GND
Red-VCC
Orange-D5
Servo Motors 2 (Left)

Brown-GND
Red-VCC
Orange-D4
Servo Motors 3 (Right Top)

Brown-GND
Red-VCC
Orange-D3
Servo Motors 4 (Right)

Brown-GND
Red-VCC
Orange-D2
IR Sensor 1 (Left)

Red-VCC
Black-GND
Yellow-A0
IR Sensor 2 (Center)

Red-VCC
Black-GND
Yellow-A1
IR Sensor 3 (Right)

Red-VCC
Black-GND
Yellow-A2
NRF24L01 (Tx) (IR Sensor, Servo, Arduino 1, LCD 1)

VCC-
GND-
CSN-
CE-
SCK-
MOSI-
NRF24L01 (Rx) (Arduino 2, LCD 2)

VCC-
GND-
CSN-
CE-
SCK-
MOSI-
