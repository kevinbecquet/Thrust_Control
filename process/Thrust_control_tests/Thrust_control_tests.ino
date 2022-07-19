
// ---------------------------------------------------------------------------
// Customize here pulse frequency as needed
#define FREQ              4000  // Output frequency in Hz
#define MIN_PULSE_LENGTH  127   // == dc 50% => 125us 
#define MAX_PULSE_LENGTH  254   // ~= dc 100% => 250us
// ---------------------------------------------------------------------------
char data;
int escPin = 12;
// ---------------------------------------------------------------------------


// Load Cell calibration
// ---------------------------------------------------------------------------
int sensorPin = 8;

#define FORCE_LOW  -5  // Minimum of the motor working range : -5 N
#define FORCE_HIGH 25  // Maximum of the motor working range : 25 N
#define FORCE_INIT 0   // Referential force used to tare the load cell

double refValue  = 219;  // Output value of the sensor when the motor is unloaded
double refForce = 0;

double SLOPE =1.0/27.0;

double lowPassLast;
bool lowPassFirst = true;
//----------------------------------------------------------------------------

//control
//----------------------------------------------------------------------------

#define ANTIWINDUP_THRESH FORCE_HIGH
double y = 0, yc = 1;
double Te = 1 / FREQ;

double Kp = 0.1 , Ki = 0, Kd = 0;//PID coef
double ui = 0, ud = 0, err = 0, err_p = 0;

//----------------------------------------------------------------------------

/*
 *  Initialisation routine
 */
void setup() {
  Serial.begin(9600);

  pinMode(escPin,OUTPUT);
  pinMode(sensorPin,INPUT);
  
  drv_pwm_setup_freq(escPin,FREQ); // setting the MCU's pwm frequency up to the desired frequency
  
  displayInstructions();
}

/*
 *  Main function
 */
void loop() {
  analogWrite(escPin,MIN_PULSE_LENGTH);
  if (Serial.available()) {
    data = Serial.read();

    switch (data) {
      // 0
      case 48 : escCalibration();
                ampCalibration();
        
        break;

      //1
      case 49 :
        Serial.println("commandProgram:\nSend values between 0 and 100% to make the motor spin accordingly");
        Serial.println("Send negative value to make the program stop");
        fStart();
        commandProgram();
        displayInstructions();

        break;

      //2
      case 50 :
        Serial.println("controlProgram:\nSend values between 0 and 100% to make the motor spin accordingly");
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
        testSensor(2000);
        displayInstructions();

        break;
        
     //5
     case 53 : Serial.println("Kp determination");
        Serial.println("Send values to make the coeficient change");
        Serial.println("Send a negative value to stop the acquisition");
        fStart();
        KProgram();
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
void escCalibration(){

  Serial.println("Calibration start");
  
  Serial.println("Sending maximum throttle");
  analogWrite(escPin,MAX_PULSE_LENGTH  );
  delay(800);

  Serial.println("Sending minimum throttle");
  analogWrite(escPin,MIN_PULSE_LENGTH  );
  delay(800);

  Serial.println("Calibration end\n\n\n");
  
}

void ampCalibration(){

 refValue = median(100,1);
 refForce = FORCE_INIT;
}

/*
 * linear mapping of a value
 */
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
 * linear mapping from a starting point (input,output) and a slope
 */
double map(double x, double input, double output, double slope){
  return (x-input) * slope + output;
}

// Command sending
//------------------------------------------------------------------

/*
 * Converts the percentage of the motor's power in the corresponding pulse length
 */
int setCommandSerial() {

  String reading = Serial.readString();
  float ratio = reading.toInt();

  int pulse = map(ratio, 0,100, MIN_PULSE_LENGTH , MAX_PULSE_LENGTH);
//  Serial.print("Ratio value in % = ");
//  Serial.println(ratio);

  if (ratio < 0 || ratio > 100) return  -1;

  return pulse;
}

/*
 * Sends the pulse length to the ESC
 */
void command(int pulse) {

  // if pulse isn't coherent value the motor stops
  if (pulse < MIN_PULSE_LENGTH   || pulse > MAX_PULSE_LENGTH  ) {
    analogWrite(escPin,MIN_PULSE_LENGTH);
    
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
 double force = map(reading, refValue, refForce, SLOPE);
 return force;
}
/*
 * return the median value of the n next acquired values
 * mode : 0 to get values converted in N | 1 to get raw values 
 */
double median(int n,int mode){

  long timer = micros();
  double tab[n] = {0};
  
  for(int i =0 ; i< n; i++){
    double force =(mode == 0 )? getForce() : analogRead(sensorPin);
    int placed = 0; 
    
    for(int j = 0; j<i; j++){
      if(tab[j] > force){
        placed = 1;
        
        double temp = tab[j];
        tab[j] = force;
        
        for(int k = j+1;k<=i;k++){
          double temp2 = tab[k];
          tab[k] = temp;
          temp = temp2;
        }
        break;
      }
      if (placed == 0) tab[i] = force;
    }
  }

  Serial.print("Median Force from ");
  Serial.print(FORCE_LOW);
  Serial.print(" to ");
  Serial.print(FORCE_HIGH);
  Serial.print(" : ");

  Serial.println(tab[(int)(n/2)]);

  Serial.print("median time in us: ");
  Serial.println(micros()-timer);
  
  return tab[(int)(n/2)];
}

double average(int n , int mode){
  long timer = micros();
  double sum = 0;

  for (int i = 0; i <n; i++){
    sum +=(mode == 0)? getForce() : analogRead(sensorPin);
    
  }
 
//  Serial.print("average time in us: ");
//  Serial.println(micros()-timer);
  
  return sum/n;
}

double lowPass(double alpha){

  double out;
  if(lowPassFirst){
    lowPassFirst = false;
    out = getForce();
   
  }
  
  else {
    out = alpha * getForce() + (1- alpha)* lowPassLast;
  }
  
  lowPassLast = out;
  return out;
  
}

void printForce(double force){
  
//   Serial.print("Average Force from ");
//  Serial.print(FORCE_LOW);
//  Serial.print(" to ");
//  Serial.print(FORCE_HIGH);
//  Serial.print(" : ");

  Serial.println(force);

}

/*
 *  Tests the load cell value acquisition
 */
void testSensor(int freq) {
  int i = 0;
  while (i >= 0) {
    
    
    if (Serial.available()) { //loop stops if we send a negative value
      String reading = Serial.readString();
      i = reading.toInt();
    }
//    long timer = micros();
    
    median(15,0);
    average(15,0);
//    int t = 1000000/freq -(micros()-timer);
//    if (t >=0) delayMicroseconds(t); // wait until the next period (2kHz)
    
    
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

  //if(ui < ANTIWINDUP_THRESH) 
    ui+= Ki*Te*err; //integral term with anti wind up
  ud = Kd / Te * (err - err_p);         //derivative term

  double u = Kp * (err + ui + ud);      //PID output

  err_p = err;

  return u;
}






double propControl(double yc, double y) {

  err = yc - y;
  
  return Kp*err;

}
//-------------------------------------------------------------------

//main functions
//-------------------------------------------------------------------
/*
 * Runs the command transmision and the sensor acquisition
 */
void commandProgram() {

  int pulse = MIN_PULSE_LENGTH, i = 0;
  
  while (pulse >= 0) { //loop stops if we send a negative value

    long timer = micros();
    
    if (Serial.available()) pulse = setCommandSerial();
    command(pulse);
    //median(25,0);
    double f = lowPass(0.01);

    
   
  Serial.print(5);
  Serial.print(0);
  
    Serial.print("F: ");
    Serial.println(f);

//    Serial.print("time : ");
//    Serial.println(micros()-timer);
  }
  Serial.println("commandProgram stopped\n\n\n");
}


/*
 * Runs the thrust controller
 */
void controlProgram() {
  int Stop = 0;
  
  while(Stop>=0){
     y = median(10,0);
     
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


void KProgram() {
  int Stop = 0;
  yc = 5;
  
  while(Stop>=0){
     y = median(25,0); // get the force
     
     double u = propControl(yc,y); // determine the force to send 

     int pulse = setCommandControl(u); // convert it in a pulse usable by the esc
     command(pulse); // send the pulse

     if(Serial.available()){ // Kp can be modified 
      
      String reading = Serial.readString();
      float temp = reading.toFloat();
      Kp = temp;
      
      if(temp<0){ // stop the program
        Stop = -1;
        Serial.println("KProgram stopped \n\n\n");
      }
      Serial.print("Kp: ");
      Serial.println(Kp);
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
  Serial.println("\t4 : Run testSensor function");
  Serial.println("\t5 : Run KProgram\n\n");
  

}
