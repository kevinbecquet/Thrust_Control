
// ---------------------------------------------------------------------------
// Customize here pulse frequency as needed
#define FREQ              4000  //Output frequency in Hz
#define MIN_PULSE_LENGTH  127   // == dc 50% => 125us 
#define MAX_PULSE_LENGTH  254   // ~= dc 100% => 250us
// ---------------------------------------------------------------------------
char data;
int escPin = 12;
// ---------------------------------------------------------------------------


// Load Cell calibration
// ---------------------------------------------------------------------------
int sensorPin = 8;

#define G 9.81 // acceleration of Earth's gravity

#define VALUE_LOW 0 //output value of the sensor when the motor is unloaded
#define FORCE_LOW -0.5 * G// Force developped by -0.5kg -> -5 N

#define VALUE_HIGH 1023 //output value of the sensor when the motor is loaded by 2.5 kg
#define FORCE_HIGH 2.5 * G // Force developped by 2 kg (F = m*g) -> 24.5 N

//----------------------------------------------------------------------------

//control
//----------------------------------------------------------------------------

#define ANTIWINDUP_THRESH FORCE_HIGH
double y = 0, yc = 1;
double Te = 1 / FREQ;

double Kp = 0, Ki = 0, Kd = 0;//PID coef
double ui = 0, ud = 0, err = 0, err_p = 0;

//----------------------------------------------------------------------------

/*
 *  Initialisation routine
 */
void setup() {
  Serial.begin(9600);

  pinMode(escPin,OUTPUT);
  
  drv_pwm_setup_freq(escPin,FREQ); // setting the MCU's pwm frequency up to the desired frequency
  
  displayInstructions();
}

/*
 *  Main function
 */
void loop() {
  if (Serial.available()) {
    data = Serial.read();

    switch (data) {
      // 0
      case 48 : calibration();
        displayInstructions();

        break;

      //1
      case 49 :
        Serial.println("Send values between 0 and 100% to make the motor spin accordingly");
        Serial.println("Send negative value to make the program stop");
        fStart();
        commandProgram();
        displayInstructions();

        break;

      //2
      case 50 :
        Serial.println("Send values between 0 and 100% to make the motor spin accordingly");
        Serial.println("Send negative value to make the program stop");
        fStart();
        controlProgram();
        displayInstructions();

        break;


      //3
      case 51 : Serial.println("Enter value between 0 and 100% of the motor speed.");
        Serial.println("Enter negative value to stop");
        fStart();
        testCommand();
        displayInstructions();
        break;

      //4
      case 52 : Serial.println("Acquisition of the load cell values");
        Serial.println("Send a negative value to stop the acquisition");
        fStart();
        testSensor();
        displayInstructions();

        break;

     
      
      default : displayInstructions();

        break;
    }
  }


}

/*
 *  Calibrates the ESC
 */
void calibration(){

  Serial.println("Calibration start");
  
  Serial.println("Sending maximum throttle");
  analogWrite(escPin,MAX_PULSE_LENGTH  );
  delay(8000);

  Serial.println("Sending maximum throttle");
  analogWrite(escPin,MIN_PULSE_LENGTH  );
  delay(8000);

  Serial.println("Calibration end\n\n\n");
  
}

/*
 * Oneshot protocol with the percentage of motor's gas and the frequency of the signal
 * not used now, kept just in case its a better way to do
 */
void oneShot(int ratio, int freq){

  int tHigh = map(ratio, 0.0,100,125,250);
  int period = 1000000/freq;
  
  digitalWrite(escPin,HIGH);
  delayMicroseconds(tHigh);
  
  digitalWrite(escPin,LOW);
  delayMicroseconds(period-tHigh);
}

/*
 * linear mapping of a value
 */
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



// Command sending
//------------------------------------------------------------------

/*
 * Converts the percentage of the motor's power in the corresponding pulse length
 */
int setCommandSerial() {

  String reading = Serial.readString();
  float ratio = reading.toInt();

  int pulse = map(ratio, 0, 100, MIN_PULSE_LENGTH  , MAX_PULSE_LENGTH  );
  Serial.print("Ratio value in % = ");
  Serial.println(ratio);

  if (ratio < 0 || ratio > 100) return  -1;

  Serial.print("Pulse length = ");
  Serial.println(pulse);
  return pulse;
}

int setCommandControl(double u){
  return map(u,0,19.62,127,254);
}

/*
 * Sends the pulse length to the ESC
 */
void command(int pulse) {

  // if pulse isn't coherent value the motor stops
  if (pulse < MIN_PULSE_LENGTH   || pulse > MAX_PULSE_LENGTH  ) {
    analogWrite(escPin,MIN_PULSE_LENGTH  );
    
  }
  else {
    analogWrite(escPin,pulse);
  }
}


/*
 * Tests the command transmission to the ESC
 */
void testCommand() {

  int pulse = 0;
  while (pulse >= 0) { //loop stops if we send a negative value
    if (Serial.available()) pulse = setCommandSerial();
    command(pulse);
  }

  Serial.println("testCommand stopped\n\n\n");
}
//---------------------------------------------------------------------------

// Load cell values reception
//---------------------------------------------------------------------------
/*
 *  Reads the data output from the AD620 amplifier and converts it in Force (N)
 */
double getForce() {

  double reading = analogRead(sensorPin);

  int force = map(reading, VALUE_LOW, VALUE_HIGH, FORCE_LOW, FORCE_HIGH);

  Serial.print("Force from ");
  Serial.print(FORCE_LOW);
  Serial.print(" to ");
  Serial.print(FORCE_HIGH);
  Serial.print(" : ");
  Serial.println(force);

  return force;
}

/*
 *  Tests the load cell value acquisition
 */
void testSensor() {
  int i = 0;
  while (i >= 0) {

    if (Serial.available()) { //loop stops if we send a negative value
      String reading = Serial.readString();
      i = reading.toInt();
    }

    getForce();
  }
  Serial.println("sensorTest stopped\n\n\n");
}

// control
//-------------------------------------------------------------------
/*
 * Returns the pwm output rate to send to the ESC
 */
double control(double yc, double y) {

  err = yc - y;

  if(ui < ANTIWINDUP_THRESH) ui+= Ki*Te*err; //integral term with anti wind up
  ud = Kd / Te * (err - err_p);         //derivative term

  double u = Kp * (err + ui + ud);      //PID output

  err_p = err;

  return u;
}

//-------------------------------------------------------------------

//main functions
//-------------------------------------------------------------------
/*
 * Runs the command transmision and the sensor acquisition
 */
void commandProgram() {

  int pulse = MIN_PULSE_LENGTH;

  while (pulse >= 0) { //loop stops if we send a negative value
    if (Serial.available()) pulse = setCommandSerial();
    command(pulse);
    getForce();
  }
  Serial.println("commandProgram stopped\n\n\n");
}


/*
 * Runs the thrust controller
 */
void controlProgram() {
  int Stop = 0;
  
  while(Stop>=0){
     y = getForce();
     
     double u = control(yc,y);

     int pulse = setCommandControl(u);
     command(pulse);

     if(Serial.available()){
      
      String reading = Serial.readString();
      float temp = reading.toFloat();
      yc = (temp < FORCE_LOW || temp > FORCE_HIGH)? yc : temp;
      
      if(temp<0) Stop = -1;
      Serial.println("controlProgram stopped \n\n\n");
     }
  }

}
//-------------------------------------------------------------------


//-------------------------------------------------------------------


/*
 * Print the starting message of a function
 */
void fStart() {

  Serial.print("Starting in 3... ");
  delay(1000);

  Serial.print("2...");
  delay(1000);

  Serial.println("1...");
  delay(1000);
}
/*
 * Displays instructions to user
 */
void displayInstructions()
{
  Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
  Serial.println("\t0 : Calibration of the ESC");
  Serial.println("\t1 : Run commandProgram");
  Serial.println("\t2 : Run controlProgram");
  Serial.println("\t3 : Run testCommand function");
  Serial.println("\t4 : Run testSensor function\n\n");
  

}
