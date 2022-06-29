# Load cell working

We need to get the thrust force produced by the motor's rotation  
That's where the load cell will come handy.

## Composition
The load cell used here is composed by a Wheatstone full bridge installed on an  
aluminium plate.

## Wheatstone bridge

![alt text](images/Wheatstone_full_bridge.jpg)

This system is initially composed by 4 resistive elements.  
When the load cell isn't loaded, these elements have the same ohmic value  
(R_1 = R_2 = R_3 = R_4 = R_G)

However, when loaded, the force applied on the load cell will deform the aluminium plaque  
which will make 2 resistors decrease and the other 2 increase.

We can determine a linear relation between the input voltage and the V_0 as the following :

![alt text](images/V_0_V_in_relation.jpg)


