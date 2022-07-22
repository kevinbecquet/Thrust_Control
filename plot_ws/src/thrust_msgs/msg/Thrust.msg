std_msgs/Header header

float64 thrust    # [N]

float64 alpha     # lowpass filter coef between 0 and 1

float64 kp        # proportionnal coef of the controller
float64 ki        # integral coef of the controller
float64 kd        # derivative coef of the controller
float64 kff       # fast forward  coef of the controller

uint8 mode          # 0 to send just a thrust command,
                    # 1 to send a controller configuration w/out a command
                    # any other int to send both 
