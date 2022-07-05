# Implementation of a Thrust Controller for a Drone Motor


## Summary
---
The goal of this project was to implement a controller allowing to control a drone using the thrust of its motors. 

## Process
---
To do so, this project is divided in [**four main steps**](https://github.com/kevinbecquet/Thrust_Control/tree/master/process):

* Acquisition of the thrust produced by the motor
* Acquisition of the command sent to the ESC
* Sending a signal to the ESC
* Creation of a controller to close the loop


# Electronics 

[Here](https://github.com/kevinbecquet/Thrust_Control/tree/master/electronics) are the main components of this system:

[![OpenCM 9.04 MCU](electronics/microcontroller/images/OpenCM-9.04-C-Microcontroller.jpg)](https://github.com/kevinbecquet/Thrust_Control/tree/master/electronics/microcontroller)  
*OpenCM 9.04 MCU board*


[![ESC](electronics/esc/images/ESC.png)](https://github.com/kevinbecquet/Thrust_Control/tree/master/electronics/esc)  
*Tiger Motor F35A 3-6s ESC BLHeli_32*

[![AD620 Module](electronics/amplifier/images/AD620_module.jpg)](https://github.com/kevinbecquet/Thrust_Control/tree/master/electronics/amplifier)  
*AD620 analog voltage amplifier module*

[![Load Cell]()](https://github.com/kevinbecquet/Thrust_Control/tree/master/electronics/loadcell)  
*Full Wheatstone bridge loadcell*





