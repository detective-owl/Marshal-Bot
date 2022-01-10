Modified Marshall Bot Code

I used the original code of HenryChu in this project but encountered some issues with it. I am trying to learn how to integrate the NRF24L01 in this system to add another wireless display.

Here is the demostration that HenryChu made (https://www.youtube.com/watch?v=_LAO7Xp4yGY&ab_channel=HenryChu). I'm trying to do this type of signals so I'll only be using 2 of the servo (https://www.youtube.com/watch?v=0Mpl4VtUABI&ab_channel=MABTechnicalTraining). 


THINGS TO DO OR ISSUES:
1. I still don't know how to make the servo move in a repeated gesture.
2. How to integrate the NRF24L01 for a secondary wireless display. 

NOTE:
1. Left Top and Right top refers to the servo facing the actual plane not the one connecting to the other servo. 
2. Left and Right IR must be pointed at the end of the wings of the aircraft and the Center IR must be directly pointed in the nose of the aircraft. 

PROBLEMS ENCOUNTERED
1. Sharp Infrared sensor is not accurate and is only consistent in specific ranges not the whole range specified in the data sheet. Putting a 200uF capacitor between the IR sensors stabilizes some of the values. Meaning you should find the working range of the IR sensor for it to be usable. The IR sensors should also not be positioned near to one another as this gives out some interference. 
2. When finding a usable range get 5 values and average them out. 

PROGRESS 
1. https://streamable.com/qh4wsc

MATERIALS USED
1. 3 Sharp IR Sensor GP2Y0A02YK0F
2. 4 SG90 Servo Motor
3. 2 Arduino Uno
4. IC2 LCD Display


ARDUINO CONNECTIONS

*LCD*                 
  1. GND-GND
  2. VCC-VCC
  3. SDA-A4
  4. SCK-A5

*Servo Motors 1 (Left Top)*
1. Brown-GND
2. Red-VCC
3. Orange-D5

*Servo Motors 2 (Left)*
1. Brown-GND
2. Red-VCC
3. Orange-D4

*Servo Motors 3 (Right Top)*
1. Brown-GND
2. Red-VCC
3. Orange-D3

*Servo Motors 4 (Right)*
1. Brown-GND
2. Red-VCC
3. Orange-D2

*IR Sensor 1 (Left)
1. Red-VCC
2. Black-GND
3. Yellow-A0

*IR Sensor 2 (Center)
1. Red-VCC
2. Black-GND
3. Yellow-A1

*IR Sensor 3 (Right)
1. Red-VCC
2. Black-GND
3. Yellow-A2

*NRF24L01 (Tx)*
1. VCC-
2. GND-
3. CSN-
4. CE-
5. SCK-
6. MOSI-

*NRF24L01 (Rx)*
1. VCC-
2. GND-
3. CSN-
4. CE-
5. SCK-
6. MOSI-
