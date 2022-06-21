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

double freq = 4000;// PWM frequency in Hz

double dc = 0; // initial duty cycle : 50 %

//control
double y,yc;
double Te = 1/freq;

double Kp = 1.1, Ki = 0, Kd=0;
double ui = 0,ud = 0,err = 0, err_p = 0;


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


double getForceCommand(){

  Serial.println("Serial acquisition...");
  String reading = Serial.readString();
  double fc  = reading.toFloat();
  
  if(fc<0 || fc>19.62){
    Serial.println("Invalid force input : enter value between 0 and 19.42");
    return 0;
  }
  else return fc;
}

// returns the pwm output rate to send to the ESC
double setCommand(double yc, double y){
 
  
  err = yc-y; 

  
  ui+= Ki*Te*err;
  ud = Kd/Te*(err-err_p);
  
  double u = Kp*(err+ui+ud);
  
  err_p = err;

 

  return u;
}


void setup() {

  Serial.begin(57600);
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  drv_pwm_setup_freq(motorPin,freq);
  
  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  Serial.println("__");
  
  if(Serial.available()){
    
   yc = getForceCommand();
  }

  if (loadcell.is_ready()){ 
    
    y = getForce();
  }
  
  
  dc = setCommand(yc,dc); //replace dc by y when the load cell is calibrated
  
  Serial.print("dc: ");
  Serial.print(dc);

  Serial.print(" | yc: ");
  Serial.println(yc);

  
  
  analogWrite(motorPin,dc);
  delay(Te*1000);

  
}
