## Modified Marshall Bot Code

I used the original code of HenryChu in this project but encountered some issues with it. I am trying to learn how to integrate the HC-12 in this system to add another wireless display.

EDIT: I found one of Henry Chu's groupmate that has the complete code but wans't able to verify if it's working because I started editing the code of Henry Chu. (https://github.com/jeffistyping/Marshall)

Here is the demostration that HenryChu made (https://www.youtube.com/watch?v=_LAO7Xp4yGY&ab_channel=HenryChu). I'm trying to do this type of signals so for now, I'll only be using 2 of the servo (https://www.youtube.com/watch?v=0Mpl4VtUABI&ab_channel=MABTechnicalTraining). 

### NOTE:
1. Left Top and Right top refers to the servo facing the actual plane not the one connecting to the other servo. 
2. Left and Right IR must be pointed at the end of the wings of the aircraft and the Center IR must be directly pointed in the nose of the aircraft. Make sure all of the sensors are in the same height. 
3. Make sure your surface is completly flat and is non reflective. This is to minimize any noise within the projecct.
4. All of your sensor must not be sagging and directly pointed to your plane. If done properly values without anything infront must be around the 100 mark.
5. During calibration it's better to take measurements after 10 mins of turning the device on. Then also get values in different lighting conditions to know the variation on data. 
6. The key to making this work is having a lot of correct data to reduce the dead spots of the device. 

### PROBLEMS ENCOUNTERED:
1. Sharp Infrared sensor is not accurate and is only consistent in specific ranges not the whole range specified in the data sheet. Putting a 200uF capacitor between the IR sensors stabilizes some of the values. Meaning you should find the working range of the IR sensor for it to be usable. The IR sensors should also not be positioned near to one another as this gives out some interference. 
2. When finding a usable range get 5 values and average them out. 
3. In the original code the servo will not move repeatedly. It would move to one position and stays there. To move the servo in a continuous motion first determine your 0 degrees (mine is in the 3 o'clock). Then to make the gestures work follow the quotations in the code given.
4. NRF24L01 will not work if you are using an LCD with an I2C interface as it confuses the NRF24L01 to transmit the data. This will make the transmission work but in a huge delay in my testing. 

### PROGRESS:
1. https://streamable.com/qh4wsc
2. https://streamable.com/149u6r
3. https://streamable.com/ekjhbb

### MATERIALS USED:
1. 3 Sharp IR Sensor GP2Y0A02YK0F
2. 4 SG90 Servo Motor (Maybe use a continuous servo motor if you want to support all of the gestures)
3. 2 Arduino Uno
4. 2 IC2 LCD Display
5. 2 HC-12 transceiver
6. NRF24L01 Arduino Libraries needed (LCD, Sharp, NRF, Servo) **This will not work if you are using an LCD library since it interfere's with the transmission)**

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

*HC-12 (Tx)* (IR Sensor, Servo, Arduino 1, LCD 1)
1. VCC-3.3v
2. GND-GND
3. TX-D9
4. RX-D10
5. Set-

*HC-12 (Rx)* (Arduino 2, LCD 2)
1. VCC-3.3v
2. GND-GND
3. TX-D0
4. RX-D1
5. Set-

*LCD*                 
1. GND-GND
2. VCC-VCC
3. SDA-A4
4. SCK-A5

**Do not use the NRF connections if you want to replicate this project**

*NRF24L01 (Tx)* (IR Sensor, Servo, Arduino 1, LCD 1)
1. VCC-VCC
2. GND-GND
3. CSN-D8
4. CE-D7
5. SCK-D13
6. MOSI-D11
7. MISO-D12

*NRF24L01 (Rx)* (Arduino 2, LCD 2)
1. VCC-VCC
2. GND-GND
3. CSN-D8
4. CE-D7
5. SCK-D13
6. MOSI-D11
7. MISO-D12

### SCHEMATICS
1. TX station
![alt text](https://github.com/detective-owl/Marshal-Bot/blob/master/Images/1.%20HC-12%20TX.png)
2. RX station
![alt text](https://github.com/detective-owl/Marshal-Bot/blob/master/Images/2.%20HC-12%20RX.png)
3. Marshall Bot without NRF24L01
![alt text](https://github.com/detective-owl/Marshal-Bot/blob/master/Images/Marshall%20Bot%20without%20wireless%20integration.png)

### MEASUREMENT CALIBRATION SUGGESTIONS BY Toph#6152
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

```
         [L sensor]         [C sensor]         [R sensor]

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


 All of the drawings and diagrams are Made by Toph#6152

### SUGGESTIONS:
1. You could use and LED Matrix to change the secondary display some of the gestures you could put is `←,→,↑,↓,x,| |`. (Suggested by Toph#6152). This is more practical since it will be more easier to read and glare won't be an issue.
2. Try using an ultrasonic sensor if you want to use this in a longer range with more consistent values. This also means your plane should be bigger since there are some interference when they are near each other.
3. A better way of automation is using a lane tracking sensor to follow the line going to the actual gate. Sensors like this would work (https://www.makerlab-electronics.com/wp-content/uploads/2017/06/Color-Sensor.jpg).
4. Try adding a LIDAR Module for the sight, LED matrix for signal interpretation, magnetic sensor if you want integrate it in the runway and in the plane. 
