# Plotting tool

This folder contains the tool used to communicate with the system from a computer.

## Requirements
* ROS2 needs to be installed. Here is a tutorial to do so:  
https://docs.ros.org/en/galactic/Installation.html

* The plotter used to display the data is plotjuggler. To install it on Ubuntu:  
```
sudo apt install ros-$ROS_DISTRO-plotjuggler-ros
```

## Description

We use a node that is able to communicate with the microcontroller through the serial port. This node is subscribed to the topic **thrust_command** so it can read the configuration messages sent to this topic and send them to the microcontroller.
It can also publish on the topic **thrust_measure** the data it gathered from the system.  
Then, plotjuggler will be able to read the data from this topic and plot it. 

## Use

1. Open 3 terminals with this folder as the current directory 
2. Compile the program 
```
colcon build --symlink-install
```
3. Source the terminals:  
```
source /opt/ros/galactic/setup.bash
source install/setup.bash
```
4. open the differents tools in the terminals:  
```
ros2 run thrust_plot thrust_plot
rqt
ros2 run plotjuggler plotjuggler
```
**thrust_plot** is the node allowing the communication with our system   
**rqt** allows to send the configurations to the system  
**plotjuggler** gathers the data sent by the node and allows to plot it  

## Send configuration messages with rqt

The messages received and published by the node are custom messages described [here](src/thrust_msgs/msg/Thrust.msg).

According to the value of the **mode** in your message, the action realised by the system will not be the same :

|Mode|Action|
|-----|-------|
|0|Send a command to the ESC|
|1|Send a controller configuration|
|2|Disable the controller and stop the motor|
|3|Tare the load cell|

To send a command, use the **thrust_command** variable.  
To send a configuration, fill each parameter with the desired values. 