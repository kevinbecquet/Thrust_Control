#!/bin/bash

for (( ; ;  ))
do 
 
    ros2 topic pub /thrust_command thrust_msgs/msg/Thrust "header:
  stamp:
    sec: 0
    nanosec: 0
  frame_id: ''
thrust: 1.0
mode: 0" -1
    
    sleep 1s

    ros2 topic pub /thrust_command thrust_msgs/msg/Thrust "header:
  stamp:
    sec: 0
    nanosec: 0
  frame_id: ''
thrust: 2.0
mode: 0" -1
    sleep 1s
done