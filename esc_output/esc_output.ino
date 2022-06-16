#include <Servo.h>

byte servoPin = 9;
Servo servo;

// linear mapping
double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//int freq = 1/0.003;
double freq = 10000;// PWM frequency in Hz
double period = 1/freq*1000000; // PWM period in us

double val2 = period/2;  

void setup() {
  
 Serial.begin(57600);
 servo.attach(servoPin);

 servo.writeMicroseconds(period/2); // send "stop" signal to ESC.

 delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  
  Serial.println("Enter PWM signal value -1 to 1, 0 to stop");
  
  while (Serial.available() == 0);
  
  double val = Serial.parseFloat(); 
  
  
  
  if(val < -1 || val > 1)
  {
    Serial.println("not valid");
  }
  else
  {

    val2 = mapd(val,-1.0,1.0,0,period);
    
    servo.writeMicroseconds(val2); // Send signal to ESC.
    Serial.println(val);
    Serial.println(val2);
  }

  
}
