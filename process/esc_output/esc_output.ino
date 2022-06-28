
/*
Can make the motor turn and chage its speed according to the sent value

/!\ drv_pwm_setup_freq(motorPin,freq) can't provide a reliable pwm signal under 1.1kHz


*/

int  motorPin = 12;

double freq = 10000;// PWM frequency in Hz

double dc = 127;  


// linear mapping
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


// returns the pwm output rate to send to the ESC
double setCommand(double val){
  
  if(val < 0 || val > 255){
    Serial.println("Not valid : Enter PWM signal value -1 to 1, 0 to stop");
    return dc;
  }
  else{
    //double dc = map(val,-1.0,1.0,0,255);
    double dc = val;
    Serial.print("Command: ");
    Serial.println(val);
    return dc;
  }
}

void setup() {
  
  Serial.begin(57600);
  drv_pwm_setup_freq(motorPin,freq);
  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  
  if(Serial.available()){
    
    Serial.println("Serial acquisition...");
    String reading = Serial.readString();
    dc = setCommand(reading.toFloat());
  }
  
  analogWrite(motorPin,dc);    
  
}
