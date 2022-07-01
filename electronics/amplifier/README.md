# Amplifier

The amplifier used in this system is an analogic amplifier, AD620 module.
![alt text](images/AD620_module.jpg)
![alt text](images/AD620_schematic.jpg)

It has two potientiometers allowing the user to tune both the offset and the gain of the input signal. 

However, this module has a voltage inverter allowing to have a -5V from a +5V supply but this component create a noise non negligeable in front of the voltage from the loadcell.
Thus, it is necessary to filter the output signal from the amplifier before sending it to the microcontroller

## Filter the noise 

The noise created by the AD620 module has a frequency around 4.5kHz and has a amplitude of 120 mV. Thus a low pass filter with a cutoff frequency of 4kHz.

### Low Pass Filter

The filter that we need to implement has to respect some constraints : 
* have a cutoff frequency of at most 4kHz -> have the good ratio between the capacitor and the resistor
* be reactive enough to allow an aqcuisition (2kHz) -> use a capacitor with a not too hig value
* not have an impedance too high compared to the micorontroller one (5%) -> use a resistor with a not too hig value

The filter implemented is an order 1 low pass filter composed by a capacitorand a resistor.
We can determine its cutoff frequency with the following equation :  
f<sub>c</sub> = 1/R\*C




## Calibration

The force range the system has to detect is from -5N to 24.5N. Knowing our microprocessor has a maximum input voltage of 3.3V we will tune the gain in order to have a voltage allowing us to have 3.3V in the input of the microprocessor when the motor poduces a force of 24.5N and 0V when it produces a -5N force.
