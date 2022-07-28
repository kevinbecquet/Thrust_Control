# Process

The implementation of the thrust controller is divided in four main steps :  
* Receive the command sent by the PixHawks
* Recieve the force values sent by the loadcell
* Create the controller determining the signal to send to the ESC
* Sending the desired signal to the ESC


## Receiving the command sent by the PixHawks
---

## Recieving the force values sent by the loadcell
---
The loadcell sends an output signal that is linear with the force it receive in input
Thus, the acquisition of the force consists in an analogRead of the output value from the amplifier that is mapped into the corresponding force in N.

#### Mapping  
* The mapping between the force and the corresponding value is a linear mapping made using one point and a slope

#### Calibration  
* At the beginning of the arduino program, the load cell is tared by getting anaverage of measurments and making it correspond to 0N.



## Create the controller determining the signal to send to the ESC
---





## Sending the desired signal to the ESC 
---
The singal sent to the ESC 
is a pwm signal following the OneShot125 protocol.



#### Calibration  
* The calibration is made by sending the signal corresponding to the maximum value and then the one corresponding to the minumun value. 



#### Send signal

* We use modified functions of the opencm 9.04 board manager preventing the signal from glitches due to the refreshing of the polarity bit

