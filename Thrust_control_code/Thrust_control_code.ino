#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 11;
const int LOADCELL_SCK_PIN = 10;

HX711 loadcell;


// Calibrating the load cell
double g = 9.81; // acceleration of Earth's gravity

double value_low = -77695; //output value of the sensor when the motor is unloaded
double force_low = 0; // motor unloaded -> 0 N

double value_high = -511700; //output value of the sensor when the motor is loaded by 2 kg
double force_high = 2*g; // Force developped by 2 kg (F = m*g)


// Calibrating data output
int  motorPin = 12;

double freq = 10100;// PWM frequency in Hz

double dc = 127; // initial duty cycle : 50 %



// linear mapping
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


// Reads the data output from the HX711 amplifier and converts it in Force (N)
double getForce(){
   
  double reading = loadcell.read();
       
  double force = map(reading, value_low, value_high, force_low, force_high); 
  
  //Serial.print("Force in N: ");
  //Serial.println(force);
   
  return force;
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
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  drv_pwm_setup_freq(motorPin,freq);
  
  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  
  if (loadcell.is_ready()){ 
    
    getForce();
  }
  
  if(Serial.available()){
    
    Serial.println("Serial acquisition...");
    String reading = Serial.readString();
    dc = setCommand(reading.toFloat());
  }
  
  analogWrite(motorPin,dc);
  
  
}
