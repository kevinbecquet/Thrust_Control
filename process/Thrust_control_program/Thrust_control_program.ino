#include "drv_pwm_mod.h"

//Timer 
HardwareTimer Timer(TIMER_CH2);

// Load Cell calibration
// ---------------------------------------------------------------------------
int sensorPin = 8;
#define FREQ          4000
#define PERIOD        1000000.0/FREQ //in us

#define FORCE_LOW     -5  // Minimum of the motor working range : -5 N
#define FORCE_HIGH    25  // Maximum of the motor working range : 25 N
#define FORCE_INIT    0   // Referential force used to tare the load cell

double refValue  = 219;   // Output value of the sensor when the motor is unloaded
double refForce = 0;

double SLOPE =1.0/27.0;

// Vibration Filter 
// ---------------------------------------------------------------------------
double filterLast;
bool filterFirst = true;

//Control
// ---------------------------------------------------------------------------
#define ANTIWINDUP_THRESH FORCE_HIGH
double y = 0.0, yc = 0.0;

double Kp = 1 , Ki = 0.0, Kd = 0.0, Kff=0.0;//PID coef
double Pout = 0.0, Iout = 0.0, Dout = 0.0, err = 0.0, err_p = 0.0;

bool ok = false;

// Customize here ESC frequency as needed
// ---------------------------------------------------------------------------
#define PWM_RES 10
int MIN_PULSE_LENGTH  = pow(2,PWM_RES-1)-1; // == dc 50% => 125us 
int MAX_PULSE_LENGTH  = pow(2,PWM_RES)-2;   // ~= dc 100% => 250us
// ---------------------------------------------------------------------------
char data;
int escPin = 12;
int pulse = MIN_PULSE_LENGTH;
// ---------------------------------------------------------------------------


// see time
// ---------------------------------------------------------------------------
long timing;
int count = 0;


void setup() {
  
  Serial.begin(9600);
  Serial.setTimeout(20);

  //Timer setting
//  Timer.stop();
//  Timer.setPeriod(PERIOD);
//  Timer.attachInterrupt(interrupt);
//  Timer.start();
  
  pinMode(sensorPin,INPUT);
  pinMode(escPin,OUTPUT);

  drv_pwm_setup_freq(escPin,FREQ); // setting the MCU's pwm frequency up to the desired frequency
  ampCalibration();
  escCalibration();
   
//  timing = micros();
}

void loop(){
  if(Serial.available()){
    String reading = Serial.readString();
    pulse  =reading.toInt(); 
    command(pulse);
//    Serial.printf("between %d & %d: %d\n",MIN_PULSE_LENGTH,MAX_PULSE_LENGTH,pulse);
  }
  int value = average(500000,1);
  Serial.printf("value at %d pulse: %d\n",pulse, value);
}


/*
 * linear mapping of a value : map(25,0,50,0,100) -> 50 
 */
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
 * linear mapping from a starting point (input,output) and a slope : map(25,0,0,2)-> 50
 */
double map(double x, double input, double output, double slope){
  return (x-input) * slope + output;
}

//Calibration
// ---------------------------------------------------------------------------
void escCalibration(){

  Serial.println("Calibration start");
  
  Serial.println("Sending maximum throttle");
  drv_pwm_set_duty_mod(escPin,PWM_RES,MAX_PULSE_LENGTH);
  delay(800);

  Serial.println("Sending minimum throttle");
  drv_pwm_set_duty_mod(escPin,PWM_RES,MIN_PULSE_LENGTH);
  delay(800);

  Serial.println("Calibration end\n\n\n");
  
}

void ampCalibration(){

 refValue = average(400,1);
 refForce = FORCE_INIT;
}


// Amplifier data acquisition
// ---------------------------------------------------------------------------

/*
 * Gets the sensor's output voltage and converts it into a force (N)
 */
double getForce() {
 
  double reading = analogRead(sensorPin);
  double force = map(reading, refValue, refForce, SLOPE);
 return force;
}
/*
 * Filters the signal recieved from the sensor
 */
double vibrationFilter(double alpha){

    double out;
  if(filterFirst){
    filterFirst = false;
    out = y;
   
  }
  
  else {
    out = alpha * y + (1- alpha)* filterLast;
  }
  
  filterLast = out;
  return out;
  
}

double average(int tim , int mode){
  
  long timer = micros();
  double sum = 0;
  int i = 0;
  
  do{
      sum +=(mode == 0)? getForce() : analogRead(sensorPin);
      i++;
  }while(micros()-timer<=tim);
  
  return sum/i;
}

//Controller
// ---------------------------------------------------------------------------
double control(double yc, double y) {

  double  FFout = Kff*yc;

  err = yc - y;
  
  Pout = Kp * err;
  //if(Iout < ANTIWINDUP_THRESH) 
    Iout+= Ki/FREQ*err; //integral term with anti wind up
  Dout = Kd *FREQ * (err - err_p);         //derivative term

    double u = FFout + Pout + Iout + Dout;      //PID output
//  u = force2PWM(u);
  
  err_p = err;
  
  return u;
}

double setForceCommand(){
  String reading = Serial.readString();
  double force = reading.toFloat();

  if (force < 0 || force > 20) return  0;
  return force;
}

// Command sending
// ---------------------------------------------------------------------------
/*
 * Determine the pulse to send the ESC using a percentage of its power
 */
int setCommandSerial() {

  String reading = Serial.readString();
  int ratio = reading.toInt();

  int pulse = map(ratio, 
                  0,
                  MIN_PULSE_LENGTH,
                  (MAX_PULSE_LENGTH - MIN_PULSE_LENGTH)/100.0);

  if (ratio < 0 || ratio > 100) return  -1;

  return pulse;
}

/*
 * Determines the pulse to tsend to the ESC according to 
 * the output of a controller
 */
double force2PWM(double f){
  // the relation between the PWM signal and the force is quadratic : 
  // f(PWM) = a*PWM^2 + b*PWM +c
  
  double a = 0.062475/1000;
  double b = 2.897058/1000;

  //we want PWM(f) so we have to reverse the relation
  double pulse;
  if(f>=(-b*b)/(4*a))pulse = -b/(2*a)+sqrt( f/a + (b*b)/(4*a*a))+MIN_PULSE_LENGTH; 
  else  pulse = -b/(2*a)-sqrt(-(f/a + (b*b)/(4*a*a)))+MIN_PULSE_LENGTH; 
    
  return pulse;
}


void command(double pulse) {

  // if pulse isn't coherent value the motor stops
  if (pulse < MIN_PULSE_LENGTH   || pulse > MAX_PULSE_LENGTH  ) {
   drv_pwm_set_duty_mod(escPin,PWM_RES,MIN_PULSE_LENGTH);
   Serial.println("stopped");
  }
  else {
     drv_pwm_set_duty_mod(escPin,PWM_RES,pulse);
  }

}
