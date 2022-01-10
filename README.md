Modified Marshall Bot Code

I used the original code of HenryChu in this project but encountered some issues with it. I am trying to learn how to integrate the NRF24L01 in this system to add another display wirelessly. 
1. Sharp Infrared sensor is not accurate and is only consistent in specific ranges not the whole range specified in the data sheet. Putting a 200uF capacitor between the IR sensors stabilizes some of the values. 

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
