Modified Marshall Bot Code

I used the original code of HenryChu in this project but encountered some issues with it. I am trying to learn how to integrate the NRF24L01 in this system to add another wireless display.

Here is the demostration that HenryChu made (https://www.youtube.com/watch?v=_LAO7Xp4yGY&ab_channel=HenryChu). I'm trying to do this type of signals so I'll only be using 2 of the servo (https://www.youtube.com/watch?v=0Mpl4VtUABI&ab_channel=MABTechnicalTraining). 


ISSUES:
1. Sharp Infrared sensor is not accurate and is only consistent in specific ranges not the whole range specified in the data sheet. Putting a 200uF capacitor between the IR sensors stabilizes some of the values. Meaning you should find the working range of the IR sensor for it to be usable.
2. I still don't know how to make the servo move in a repeated gesture and how to integrate the NRF24L01 for a secondary wireless display. 

NOTE:
1. Left Top and Right top refers to the servo facing the actual plane not the one connecting to the other servo. 

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
