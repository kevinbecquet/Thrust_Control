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
        self.ser_.port = '/dev/ttyACM0' # serial port
        self.ser_.baudrate = 9600
        self.ser_.timeout = 10 # specify timeout when using readline()
        self.ser_.open()

    def listener_callback(self,msg):
        
        config_msg = ",".join([str(msg.mode),
                            str(msg.thrust_comm),
                            str(msg.alpha),
                            str(msg.kp),
                            str(msg.ki),
                            str(msg.kd),
                            str(msg.kff)])
        print("Configuration sent: ",end = '')                    
        print(config_msg)
        self.ser_.write(config_msg.encode())
        

    def timer_callback(self): 
        

        if(self.ser_.inWaiting()>0):
            self.ser_.readline() # reads the first line (very likely to be incomplete thus unusable)
            line=self.ser_.readline().decode()
            line_as_list = line.split(',')      
            msg = Thrust()
            
            msg.thrust_meas = float(line_as_list[0])
            msg.thrust_comm = float(line_as_list[1])
            msg.thrust_comp = float(line_as_list[2])
            msg.kp = float(line_as_list[3])
            msg.ki = float(line_as_list[4])
            msg.kd = float(line_as_list[5])
            msg.kff = float(line_as_list[6])
            msg.pulse = int(line_as_list[7])

            self.publisher_.publish(msg)
            
       

def main(args=None):
    rclpy.init(args=args)

    thrust_plot = ThrustPlot()

    rclpy.spin(thrust_plot)

    thrust_plot.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
