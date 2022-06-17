


int  motorPin = 12;


// linear mapping
double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//PWM 
void pwm(double period,double dc,int pin){
    
    digitalWrite(pin,HIGH);
    delayMicroseconds(dc);
    digitalWrite(pin,LOW);
    delayMicroseconds(period - dc);   
}



//int freq = 1/0.003;
double freq = 10000;// PWM frequency in Hz



double period = 1/freq*1000000; // PWM period in us

double val2 = period/2;  

void setup() {
  
 Serial.begin(57600);

 delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  
  //change tha value if another one has been entered
  if(Serial.available()){
           
      String reading = Serial.readString();
      double val = reading.toFloat(); 
      
      if(val < -1 || val > 1)
        Serial.println("Not valid : Enter PWM signal value -1 to 1, 0 to stop");
      
      else{
        val2 = mapd(val,-1.0,1.0,0,period);
        Serial.print(" | val: ");
        Serial.println(val);
        
      }
    }

    // send a PWM cycle to the esc
    pwm(period,val2,motorPin);
    
    Serial.print("val2: ");
    Serial.println(val2);

    

   
    
    
    
  
}
