#include "drv_pwm_mod.h"

//Timer 
HardwareTimer Timer(TIMER_CH2);

#define FREQ          4000                  // in Hz
double PERIOD  = 1000000.0/FREQ;            // in us


// ESC settings
#define PWM_RES 10                          // resolution of the PWM signal sent to the ESC
int MIN_PULSE_LENGTH  = pow(2,PWM_RES-1)-1; // == dc 50% => 125us 
int MAX_PULSE_LENGTH  = pow(2,PWM_RES)-2;   // ~= dc 100% => 250us

int escPin = 12;
double pulse = MIN_PULSE_LENGTH;


// Load Cell calibration
int sensorPin = 8;
#define FORCE_LOW     -5  // Minimum of the motor working range : -5 N
#define FORCE_HIGH    25  // Maximum of the motor working range : 25 N
#define FORCE_INIT    0   // Referential force used to tare the load cell

double refValue  = 219;   // Output value of the sensor when the motor is unloaded
double refForce = 0;
double SLOPE =1.0/27.0; //coef of linear relation between the values from the amplifier and the corresponding thrust


// Vibration Filter 
double filterLast;
bool filterFirst = true;
double alpha = 0.01; // filter coef 


//Control
#define ANTIWINDUP_THRESH FORCE_HIGH
double thrust_measure = 0.0, thrust_command = 1.0,thrust_compute;

double Kp = 1 , Ki = 1.0, Kd = 0.0, Kff=0.8;//PID coef
double Pout = 0.0, Iout = 0.0, Dout = 0.0, FFout = 0.0, err = 0.0, err_p = 0.0;

bool control_start = false;


void setup(){
  
  Serial.begin(9600);

  //Timer setting
  Timer.stop();
  Timer.setPeriod(PERIOD);
  Timer.attachInterrupt(interrupt);
  Timer.start();


  // pin setting
  pinMode(sensorPin,INPUT);
  pinMode(escPin,OUTPUT);


  drv_pwm_setup_freq(escPin,FREQ); // sets the MCU's pwm frequency up to the desired frequency


  // calibrations
  ampCalibration();
  escCalibration();
   

}

void loop(){

}

void interrupt(){
   
  if (Serial.available()){ //if a configuration message is available
    
    control_start = true;
    readConfigMsg();     
  }  
  
  getForce(&thrust_measure);
  vibrationFilter(&thrust_measure);
 
  if(control_start){
    
    control(thrust_command,thrust_measure,&thrust_compute);  
    force2PWM(thrust_compute,&pulse);    
    command(&pulse);  
  }

  Serial.printf("%f\n",thrust_measure);
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

/*
 * Calibrates the ESC for signals using Oneshot125 protocol
 */
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

/*
 * Tares the load cell 
 */
void ampCalibration(){

 refValue = average(400,1);
 refForce = FORCE_INIT;
}


/*
 * Gets the sensor's output voltage and converts it into a force (N)
 */
void getForce(double* force) {

   *force = map(analogRead(sensorPin), refValue, refForce, SLOPE);
}

/*
 * Low Pass filter : y(k) = alpha* x(k) + (1-alpha)*y(k-1)
 */
void vibrationFilter(double* force){

  if(filterFirst){
    filterFirst = false;
    *force = thrust_measure;
  }
  
  else {
    *force = alpha * thrust_measure + (1- alpha) * filterLast;
  }
  
  filterLast = *force;  
}


double average(int tim , int mode){
  
  long timer = micros();
  double sum = 0,force;
  int i = 0;
  
  do{
      getForce(&force);
      sum +=(mode == 0)? force : analogRead(sensorPin);
      i++;
  }while(micros()-timer<=tim);
  
  return sum/i;
}

/*
 * Computes the force to send to the motor using a PID controller
 */
double control(double thrust_command, double thrust_measure, double* thrust_compute) {

  FFout = Kff*thrust_command;

  err = thrust_command - thrust_measure;
  
  Pout = Kp * err;
  //if(Iout < ANTIWINDUP_THRESH) 
    Iout+= Ki/FREQ*err; //integral term with anti wind up
  Dout = Kd *FREQ * (err - err_p);         //derivative term

  *thrust_compute = FFout + Pout + Iout + Dout;      //PID output
  
  err_p = err;
}


void readConfigMsg(){

     float configArray[7] = {-1,-1,-1,-1,-1,-1,-1};
     String reading  = Serial.readString();
     char* parsed;  
     char* parsingElt =",";
     int i = 0;
     
     parsed = strtok(&reading[0],parsingElt);
     int mode = atoi(parsed);
     
     while(parsed != NULL && i< 7){
      
      configArray[i] = atof(parsed);
      parsed= strtok(NULL,parsingElt);
      i++;
      
     }
     if ( mode != 1) thrust_command = (configArray[1]>=0)? configArray[1] : thrust_command;
     
     if(mode != 0){
     
       alpha = (configArray[2]>=0)? configArray[2] : alpha;
       Kp    = (configArray[3]>=0)? configArray[3] : Kp;
       Ki    = (configArray[4]>=0)? configArray[4] : Ki;
       Kd    = (configArray[5]>=0)? configArray[5] : Kd;
       Kff   = (configArray[6]>=0)? configArray[6] : Kff;
     }
     
     if (thrust_command == 0) control_start = false;
     Serial.printf("Config : %2f %2f %2f %2f %2f %2f %2f\n",mode,thrust_command,alpha,Kp,Ki,Kd,Kff);
}



/*
 * Determines the pulse to tsend to the ESC according to 
 * the output of a controller
 */
double force2PWM(double f,double* pulse){
  // the relation between the PWM signal and the force is quadratic : 
  // f(PWM) = a*PWM^2 + b*PWM +c
  
  static double a = 0.062475/1000;
  static double b = 2.897058/1000;

  //we want PWM(f) so we have to reverse the relation
  
  if(f>=(-b*b)/(4*a)) *pulse = -b/(2*a)+sqrt( f/a + (b*b)/(4*a*a))+MIN_PULSE_LENGTH; 
  else  *pulse = -b/(2*a)-sqrt(-(f/a + (b*b)/(4*a*a)))+MIN_PULSE_LENGTH; 
}

/*
 * Sets the PWM signal and send to the ESC
 */
void command(double* pulse) {

  // if pulse isn't coherent value the motor stops
  if (*pulse < MIN_PULSE_LENGTH   || *pulse > MAX_PULSE_LENGTH  ){
    
   drv_pwm_set_duty_mod(escPin,PWM_RES,MIN_PULSE_LENGTH);
  }
  else {
    
     drv_pwm_set_duty_mod(escPin,PWM_RES,*pulse);
  }
}
