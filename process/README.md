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



## Create the controller determining the signal to send to the ESC
---





## Sending the desired signal to the ESC 
---
The singal sent to the ESC 
is a pwm signal following the OneShot125 protocol.

But before even sending any signal to the ESC, it is necessary to calibrate this component in order to get the reaction we want from the sent signal.

### Calibration
-----
The calibration is made by sending the signal corresponding to the maximum value and then the one corresponding to the minumun value. 



### Send signal
---

In the code the signals sent are created with *analogRead(pin,value)* from the arduino library (a function allowing to send a PWM signal with a duty cycle editable using its value argument : 0 for a 0% dc and 255 for a 100% dc).

Here the max value used is not "255" but 254 because a a pwm signal with a 255 value is a continuous signal. However, we need the signal to go down to allow the ESC to detect the frequency.

