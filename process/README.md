# Process

The implementation of the thrust controller is divided in four main steps :  
* Receive a thrust command 
* Receive the force values sent by the loadcell
* Create the controller determining the signal to send to the ESC
* Sending the desired signal to the ESC


## Receiving a command
The communication with the microcontroller is made through the serial port. Our system sends its data using a message on one line that has the following structure:  

measurement,command,controller_output,proportionnal_part,Integral_part,derivative_part,feedforward_part,pulse_sent  

We can also sent configuration using the following message structure: 

mode,command,vibration_filter_coef,controller_proportionnal_coef,controller_integral_coef,controller_derivative_coef,controller_feedforward_coef

As this can be annoying to write and read each time, [we made a tool](../plot_ws/) allowing an easier control of the system and an easier reading of its data by using ros2 and plotjuggler.


## Recieving the force values sent by the loadcell

The loadcell sends an output signal that is linear with the force it receive in input
Thus, the acquisition of the force consists in an analogRead of the output value from the amplifier that is mapped into the corresponding force in N.

#### Mapping 

* The mapping between the force and the corresponding value is a linear mapping made using one point and a slope

#### Calibration  

* When the microcontroller is powered up, the load cell is tared by getting an average of measurments and making it correspond to 0N.



## Create the controller determining the signal to send to the ESC

The controller used is a PID with a feedforward term added to it.
The integral part is limited by an antiwindup threshold stopping the integration in case the system is saturated.
 
The derivative part derivates the measurement and not the error.  
The derivation operation used is not a proper deriavtion but an approximation of it :  
In the Laplace domain, a derivation becomes a multipication by s (the Laplacian variable). However, the derivation used here corresponds to a multiplication by s/(ε*s + 1). This approximation is made to limit the amplification of the noise made by the derivation operation.

The feedforward term is the answer of the system in open loop. Using it allows a faster response as the controller doesn't have to do all the work to go to the value setted in command. 




## Sending the desired signal to the ESC 

The signal sent to the ESC is a pwm signal following the OneShot125 protocol: a throttle of 125μs is the minimum, corresponding to a stopped motor, and a throttle of 250μs is the maximum, corresponding to a motor going at full power.

Thus, to be as fast as possible, the PWM signal that is sent to the ESC has a frequency of 4kHz (and a period of 250μs). Moreover the signal's resolution has been set to 10 bits to be precise enough


#### Calibration  

* The calibration is made by sending the signal corresponding to the maximum value and then the one corresponding to the minumun value. 

#### Thrust / Signal mapping

The relation between the length of the throttle sent to the motor and the thrust produced by the motor is quadratic.  
To map these values making some measurements is necessary. 
Then, we need to find a fitting function in the form f(PWM) = a\*PWM² + b\*PWM  
![F2PWM_Measurements]()

Finally, it is possible to implement the reverted function PWM(f) with the a and b coeficients found previously.


#### Send signal

* Some functions of the drv_pwm files of the opencm 9.04 board manager preventing the signal from glitches due to the refreshing of the polarity bit

