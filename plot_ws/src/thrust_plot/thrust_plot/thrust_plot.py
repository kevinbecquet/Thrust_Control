import rclpy
from rclpy.node import Node

import serial

from thrust_msgs.msg import Thrust


class ThrustPlot(Node):

    def __init__(self):
        super().__init__('thrust_plot')
        self.publisher_ = self.create_publisher(Thrust, 'thrust_measure', 10)
        
        self.subscriber_ =self.create_subscription(
            Thrust,
            'thrust_command',
            self.listener_callback,
            10)
        
        
        
        timer_period = 0.000250  # seconds
        self.timer_ = self.create_timer(timer_period, self.timer_callback)


        self.ser_ = serial.Serial()
        self.ser_.port = '/dev/ttyACM0' #Arduino serial port
        self.ser_.baudrate = 9600
        self.ser_.timeout = 10 #specify timeout when using readline()
        self.ser_.open()

    def listener_callback(self,msg):
        
        config_msg = ",".join([str(msg.thrust),
                            str(msg.alpha),
                            str(msg.kp),
                            str(msg.ki),
                            str(msg.kd),
                            str(msg.kff)])
        print("Configuration sent: ",end = '')                    
        print(config_msg)
        self.ser_.write(config_msg.encode())
        

    def timer_callback(self): 
        self.ser_.readline() #read the first line (very likely to be incomplete thus unusable)

        if(self.ser_.inWaiting()>0):
            line=self.ser_.readline().decode('utf-8')
            line_as_list = line.split(',')      
            msg = Thrust()
            #msg.thrust = float(line_as_list[1])
            msg.thrust = float(line)
            self.publisher_.publish(msg)
       

def main(args=None):
    rclpy.init(args=args)

    thrust_plot = ThrustPlot()

    rclpy.spin(thrust_plot)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    thrust_plot.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
