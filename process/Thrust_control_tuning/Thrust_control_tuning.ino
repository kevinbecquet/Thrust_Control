#include "drv_pwm_mod.h"

//Timer
HardwareTimer Timer(TIMER_CH2);

#define FREQ          4000                  // in Hz
float PERIOD  = 1000000.0 / FREQ;          // in us
float PERIOD_S = 1.0 / FREQ;


// ESC settings
#define PWM_RES 10                          // resolution of the PWM signal sent to the ESC
int MIN_PULSE_LENGTH  = pow(2, PWM_RES - 1) - 1; // == dc 50% => 125us
int MAX_PULSE_LENGTH  = pow(2, PWM_RES) - 2; // ~= dc 100% => 250us

int escPin = 12;
int pulse = MIN_PULSE_LENGTH;


// Load Cell calibration
int sensorPin = 8;
#define FORCE_LOW     -5  // Minimum of the motor working range : -5 N
#define FORCE_HIGH    25  // Maximum of the motor working range : 25 N
#define FORCE_INIT    0   // Referential force used to tare the load cell

float refValue  = 219;   // Output value of the sensor when the motor is unloaded
float refForce = 0;
float SLOPE = 0.029113972; //coef of linear relation between the values from the amplifier and the corresponding thrust


// Vibration Filter
bool filterFirst = true;
float alpha = 0.005; // filter coef


//Control
#define ANTIWINDUP_THRESHUP 16 
#define ANTIWINDUP_THRESHDOWN 0
float thrust_current = 0.0, thrust_command = 0.0, thrust_compute = 0.0, thrust_previous = 0.0;

float Kp = 3.5 , Ki = 6.0, Kd = 0.005, Kff = 0.8; //PID coef
float Pout = 0.0, Iout = 0.0, Dout = 0.0, Dout_prev = 0.0, FFout = 0.0, err = 0.0, err_p = 0.0;
float derivative_approx = 0.000001;

bool control_start = false, integral_start = false;


void setup() {

  Serial.begin(9600);
  Serial.setTimeout(20);
  
  // pin setting
  pinMode(sensorPin, INPUT);
  pinMode(escPin, OUTPUT);


  drv_pwm_setup_freq(escPin, FREQ); // sets the MCU's pwm frequency up to the desired frequency


  // calibrations
  ampCalibration(1000);
  escCalibration(800);

  
  //Timer setting
  Timer.stop();
  Timer.setPeriod(PERIOD);
  Timer.attachInterrupt(interrupt);
  Timer.start();

}

void loop() {

}

void interrupt() {

  if (Serial.available()) { //if a configuration message is available

    readConfigMsg();
  }

  getForce(&thrust_current);
  vibrationFilter(&thrust_current, &thrust_previous);

  if (control_start) {

    control(thrust_command, &thrust_compute);
    force2PWM(thrust_compute, &pulse);
    command(&pulse);
  }

  thrust_previous  = thrust_current;

  Serial.printf("%f,%f,%f,%f,%f,%f,%f,%d\n",thrust_current,thrust_command,thrust_compute,Pout,Iout,Dout,FFout,pulse);

  //  Serial.printf("%f\n",thrust_current);
}


/*
   linear mapping of a value : map(25,0,50,0,100) -> 50
*/
float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
   linear mapping from a starting point (input,output) and a slope : map(25,0,0,2)-> 50
*/
float map(float x, float input, float output, float slope) {
  return (x - input) * slope + output;
}

/*
   Calibrates the ESC for signals using Oneshot125 protocol
*/
void escCalibration(int tim) {

  //sends max throttle
  drv_pwm_set_duty_mod(escPin, PWM_RES, MAX_PULSE_LENGTH);
  delay(tim);

  //sends min throttle
  drv_pwm_set_duty_mod(escPin, PWM_RES, MIN_PULSE_LENGTH);
  delay(tim);
}

/*
   Tares the load cell by doing an average of the signal values received from amplifier that have been filtered
*/
void ampCalibration(int tim) {

  long timer = millis();
  float sum = 0.0, val= 0,val_p = 0.0;
  int i = 0;

  do {
    val = analogRead(sensorPin);
    vibrationFilter(&val,&val_p);
    
    sum += val;
    val_p = val;
    i++;
  } while (millis() - timer <= tim);
  
  refValue = sum/i;
  refForce = FORCE_INIT;
}


/*
   Gets the sensor's output voltage and converts it into a force (N)
*/
void getForce(float* force) {

  *force = map(analogRead(sensorPin), refValue, refForce, SLOPE);
}

/*
   Low Pass filter : y(k) = alpha* x(k) + (1-alpha)*y(k-1)
*/
void vibrationFilter(float* force, float* force_previous) {

  if (filterFirst) {
    filterFirst = false;
  }

  else {
    *force = alpha * (*force) + (1 - alpha) * (*force_previous);
  }
}


/*
   Computes the force to send to the motor using a PID controller
*/
float control(float thrust_command, float* thrust_compute) {
  
  err = thrust_command - thrust_current;

  FFout = Kff * thrust_command;

  Pout = Kp * err;

  

  Dout = (derivative_approx * Dout_prev + Kd * (thrust_current - thrust_previous)) / (PERIOD_S + derivative_approx);

  *thrust_compute = FFout + Pout + Iout + Dout;      //PID output
  
  if ((*thrust_compute <= ANTIWINDUP_THRESHUP) && (*thrust_compute >= ANTIWINDUP_THRESHDOWN)) {
    
     Iout += Ki / FREQ * err; //integration of the error if the output is not saturated
    *thrust_compute = FFout + Pout + Iout + Dout;
  }
  
  err_p = err;
  Dout_prev = Dout;
}

/*
   Determines the pulse to tsend to the ESC according to
   the output of a controller
*/
float force2PWM(float f, int* pulse) {
  // the relation between the PWM signal and the force is quadratic :
  // f(PWM) = a*PWM^2 + b*PWM +c

  static float a = 0.0531357384 / 1000;
  static float b = 5.2463901262 / 1000;

  //we want PWM(f) so we have to reverse the relation

  if (f >= (-b * b) / (4 * a)) *pulse = -b / (2 * a) + sqrt( f / a + (b * b) / (4 * a * a)) + MIN_PULSE_LENGTH;
  else  *pulse = -b / (2 * a) - sqrt(-(f / a + (b * b) / (4 * a * a))) + MIN_PULSE_LENGTH;

}

/*
   Sets the PWM signal and send to the ESC
*/
void command(int* pulse) {

  *pulse = constrain(*pulse, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  drv_pwm_set_duty_mod(escPin, PWM_RES, *pulse);



}



void readConfigMsg() {

  float configArray[7] = { -1, -1, -1, -1, -1, -1, -1};
  String reading  = Serial.readString();


  char* parsed;
  char* parsingElt = ",";
  

  parsed = strtok(&reading[0], parsingElt);
  int mode = atoi(parsed);

  if ( mode == 2 || mode == 3) { // stops the motor and disables the controller
    control_start = false;

    pulse = MIN_PULSE_LENGTH;
    command(&pulse);

    Pout = 0; Iout = 0; Dout = 0; Dout_prev = 0; FFout = 0;
    err = 0; err_p = 0;
    thrust_compute = 0.0; thrust_command = 0.0;

    if (mode == 3) ampCalibration(3000);

    return;
  }

  int i = 0;
  while (parsed != NULL && i < 7) {

    configArray[i] = atof(parsed);
    parsed = strtok(NULL, parsingElt);
    i++;

  }

  if ( mode != 1) {
    thrust_command = (configArray[1] >= 0) ? configArray[1] : thrust_command;
    control_start = true;
  }

  if (mode != 0) {

    alpha = (configArray[2] >= 0) ? configArray[2] : alpha;
    Kp    = (configArray[3] >= 0) ? configArray[3] : Kp;
    Ki    = (configArray[4] >= 0) ? configArray[4] : Ki;
    Kd    = (configArray[5] >= 0) ? configArray[5] : Kd;
    Kff   = (configArray[6] >= 0) ? configArray[6] : Kff;
  }
}
