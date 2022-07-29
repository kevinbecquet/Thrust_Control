std_msgs/Header header

float64 thrust_meas # thrust measurement [N]
float64 thrust_comm # thrust command sent to the system [N]
float64 thrust_comp # controller's output thrust [N] 

float64 alpha       # vibration filter coef between 0 and 1
float64 kp          # proportionnal coef of the controller
float64 ki          # integral coef of the controller
float64 kd          # derivative coef of the controller
float64 kff         # feedforward coef of the controller

uint16 pulse        # 10 bits encoded PWM sent to the ESC 

uint16 mode         # 0 to send just a thrust command,
                    # 1 to send a controller configuration w/out a command
                    # 2 to disable the controller and stop the motor
                    # 3 to tare the sensor