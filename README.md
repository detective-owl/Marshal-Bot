## Modified Marshall Bot Code

I used the original code of HenryChu in this project but encountered some issues with it. I am trying to learn how to integrate the NRF24L01 in this system to add another wireless display.

EDIT: I found one of Henry Chu's groupmate that has the complete code but wans't able to verify if it's working because I started editing the code of Henry Chu. (https://github.com/jeffistyping/Marshall)

Here is the demostration that HenryChu made (https://www.youtube.com/watch?v=_LAO7Xp4yGY&ab_channel=HenryChu). I'm trying to do this type of signals so for now, I'll only be using 2 of the servo (https://www.youtube.com/watch?v=0Mpl4VtUABI&ab_channel=MABTechnicalTraining). 


### THINGS TO DO OR ISSUES:
1. How to integrate the NRF24L01 for a secondary wireless display. 

### NOTE:
1. Left Top and Right top refers to the servo facing the actual plane not the one connecting to the other servo. 
2. Left and Right IR must be pointed at the end of the wings of the aircraft and the Center IR must be directly pointed in the nose of the aircraft. 
3. Make sure your surface is completly flat and is non reflective. This is to minimize any noise within the projecct.
4. All of your sensor must not be sagging and directly pointed to your plane. If done properly values without anything infront must be aroung the 100 mark.

### PROBLEMS ENCOUNTERED:
1. Sharp Infrared sensor is not accurate and is only consistent in specific ranges not the whole range specified in the data sheet. Putting a 200uF capacitor between the IR sensors stabilizes some of the values. Meaning you should find the working range of the IR sensor for it to be usable. The IR sensors should also not be positioned near to one another as this gives out some interference. 
2. When finding a usable range get 5 values and average them out. 
3. In the original code the servo will not move repeatedly. It would move to one position and stays there. To move the servo in a continuous motion first determine your 0 degrees (mine is in the 3 o'clock). Then to make the gestures work follow the quotations in the code given.

### PROGRESS:
1. https://streamable.com/qh4wsc
2. https://streamable.com/149u6r
3. https://streamable.com/ekjhbb

### MATERIALS USED:
1. 3 Sharp IR Sensor GP2Y0A02YK0F
2. 4 SG90 Servo Motor (Maybe use a continuous servo motor if you want to support all of the gestures)
3. 2 Arduino Uno
4. IC2 LCD Display

### SENSOR CALIBRATION SUGGESTIONS BY Toph#6152
Measurement Suggestions:
`Go Straight:`
1) Plane in middle of runway (far end);
2) Get average reading of C, this is your GoStraight_C_Max value;
3) Plane still in middle but now close to "Stop" (but barely there);
4) Get average reading of C, this is your GoStraight_C_Min value;
^ while you're doing this, the min/max values for L & R sensors should be the close to the same at C_Min or C_Max 

`Go Left:`
1) Plane in right of runway (far end);
2) Get average reading of R, this is your GoLeft_R_Max value;
3) Plane still in the right but now closer to "Stop";
4) Get average reading of R, this is your GoLeft_R_Min value;
^ while you're doing this, the min/max values for L & C sensors should be the close to the same at R_Min or R_Max 


### Diagrams:


1. Calibration when the left and right won't work.
```
        [L sensor]         [C sensor]         [R sensor]

stop - - - - - - - - - - - - - - - - - - - - - - - - - - - -


            /\ 
           |  |
      ____/    \_____
     /______   ______\
           |  |
          /_\/_\
```
*This is for your GoLeft L min*


         [L sensor]         [C sensor]         [R sensor]
```
stop - - - - - - - - - - - - - - - - - - - - - - - - - - - -








            /\ 
           |  |
      ____/    \_____
     /______   ______\
           |  |
          /_\/_\
 - - - - - - - - - - - - end of runway - - - - - - - - - - -
 ```
 *This is for your GoLeft L max*
 
2. Notes for people who want to do this is the future.
```
           180°       0°
            /          \
           /            \
     _____/             _\_________
    |  ()     |         |   ()     |
    | leftTop |         | rightTop |
    |/        |         |     \    |
    /------             -------\----
   /   []                  []   \
 0°____[]___           ____[]____ 180°
  | left    |         | right    |
   ---------           ----------
```
 *This is for the configuration of the servo*
 
  ```
     |X|               ___________
     |X|sensor]       /   the Plane
     |X||X|           \___________
     |X||X|
       \__\______ foam boards
 ```
 *Sensor mounting suggestion*
 
 ```
               | Left  |  Center | Right |
              |Min|Max| Min|Max |Min|Max|
| Go Straight | 40| 40| 32 | 55 | 50| 56|
| Go Left     | 40| 40| 50 | 55 | 30| 54|
| Go Right    | 30| 54| 50 | 55 | 40| 40|
```
*Values to be expected when calibrating your `Turn Left` and `Turn Right` *


 All of the drawings and diangrams are Made by Toph#6152

### ARDUINO CONNECTIONS:

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

*IR Sensor 1 (Left)*
1. Red-VCC
2. Black-GND
3. Yellow-A0

*IR Sensor 2 (Center)*
1. Red-VCC
2. Black-GND
3. Yellow-A1

*IR Sensor 3 (Right)*
1. Red-VCC
2. Black-GND
3. Yellow-A2

*NRF24L01 (Tx)* (IR Sensor, Servo, Arduino 1, LCD 1)
1. VCC-
2. GND-
3. CSN-
4. CE-
5. SCK-
6. MOSI-

*NRF24L01 (Rx)* (Arduino 2, LCD 2)
1. VCC-
2. GND-
3. CSN-
4. CE-
5. SCK-
6. MOSI-
