#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 11;
const int LOADCELL_SCK_PIN = 10;

HX711 loadcell;


// Calibrating the load cell
double g = 9.81; // acceleration of Earth's gravity

double value_low = -77695; //output value of the sensor when the motor is unloaded
double force_low = 0; // motor unloaded -> 0N

double value_high = -511700; //output value of the sensor when the motor is loaded by 2kg
double force_high = 2*g; // Force developped by 2kg (F = m*g)


int  motorPin = 12;

//double freq = 1/0.003;
double freq = 10000;// PWM frequency in Hz
double period = 1/freq*1000000; // PWM period in us

double dc = period/2; 



// linear mapping
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//PWM 
void pwm(double period,double dc,int pin){
    
    digitalWrite(pin,HIGH);
    delayMicroseconds(dc);
    digitalWrite(pin,LOW);
    delayMicroseconds(period - dc);   
}

// read the value from the HX711 amplifier and convert it in Force (N)
double getForce(){
   
    double reading = loadcell.read();
    //Serial.print("Result in unit: ");
    //Serial.print(reading);
    
    double force = map(reading, value_low, value_high, force_low, force_high); 
    //Serial.print(" | Result in N: ");
    //Serial.println(force,2);
 

  
 return force;
}


// return the pwm output to send to the ESC
double setCommand(double val){
  
   if(val < -1 || val > 1){
        Serial.println("Not valid : Enter PWM signal value -1 to 1, 0 to stop");
        return -1;
   }
      else{
        double dc = map(val,-1.0,1.0,0,period);
        Serial.print(" | val: ");
        Serial.println(val);
        return dc;
      }
  }


void setup() {

  Serial.begin(57600);
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);


  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  // put your main code here, to run repeatedly:


  if (loadcell.is_ready()){ 
    getForce();
  }
  if(Serial.available())
  {
    String reading = Serial.readString();
    dc = setCommand(reading.toFloat);
  }
  
  pwm(period,dc,motorPin);
  
  
}
