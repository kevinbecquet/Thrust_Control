

#include <Servo.h>
// ---------------------------------------------------------------------------
// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000// Maximum pulse length in µs
// ---------------------------------------------------------------------------
Servo esc;
char data;
// ---------------------------------------------------------------------------


// Load Cell calibration
// ---------------------------------------------------------------------------
int sensorPin = 8;

double g = 9.81; // acceleration of Earth's gravity

double value_low = 0; //output value of the sensor when the motor is unloaded
double force_low =0;// -0.5 * g; // Force developped by -0.5kg -> -5 N

double value_high = 1023; //output value of the sensor when the motor is loaded by 2.5 kg
double force_high = 255;//2.5 * g; // Force developped by 2 kg (F = m*g) -> 24.5 N

//----------------------------------------------------------------------------

//control
//----------------------------------------------------------------------------
double y, yc;
double Te = 1 / freq;

double Kp = 1.1, Ki = 0, Kd = 0;//PID coef
double ui = 0, ud = 0, err = 0, err_p = 0;

//----------------------------------------------------------------------------

/**
 * Initialisation routine
 */
void setup() {
    Serial.begin(9600);
    
    esc.attach(12, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
   
    
    displayInstructions();
}

/**
 * Main function
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
            case 50 : Serial.println("Enter value between 0 and 100% of the motor speed.");
                      Serial.println("Enter negative value to stop");
                      fStart();
                      testCommand();
                      displayInstructions();
            break;

            //3
            case 51 : Serial.println("Acquisition of the load cell values");
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
 * Calibration of the ESC
 */
void calibration(){

  Serial.println("Calibration start");
  Serial.println("Sending maximum throttle");
  esc.writeMicroseconds(MAX_PULSE_LENGTH);

  delay(8000);

  Serial.println("Sending minimum throttle");
  esc.writeMicroseconds(MIN_PULSE_LENGTH);

  delay(8000);  

  Serial.println("Calibration end\n\n\n");
}


/*
 * linear mapping of a value 
 */
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
 * Print the starting message of a function
 */
void fStart(){

  Serial.print("Starting in 3... ");
  delay(1000);
  
  Serial.print("2...");
  delay(1000);
  
  Serial.println("1...");
  delay(1000);
}

// Command sending
//------------------------------------------------------------------

/*
 * Conversion of the percentage of the speed of the motor in the corresponding pulse length
 */
int setCommandSerial(){

  String reading = Serial.readString();
  float ratio = reading.toInt();
  
  int pulse = map(ratio,0,100,MIN_PULSE_LENGTH,MAX_PULSE_LENGTH);
  
  Serial.print("Ratio value in % = ");
  Serial.println(ratio);
  
  if(ratio < 0) return  -1;
  
  // Serial.print("Pulse length = ");
  // Serial.println(pulse);
  return pulse;
}


/*
 * Send the pulse length to the ESC
 */
void command(int pulse){

    // if pulse isn't coherent value the motor stops
    if(pulse<MIN_PULSE_LENGTH || pulse >MAX_PULSE_LENGTH){
      
      esc.writeMicroseconds(MIN_PULSE_LENGTH);
      delay(200);
    }
    else{
     esc.writeMicroseconds(pulse);
     delay(200);
    }
}
   

/*
 * test the command transmission to the ESC
 */
void testCommand(){

  int pulse = 0;
  while(pulse>=0){//loop stops if we send a negative value
    if(Serial.available()) pulse = setCommand();
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

  int force = map(reading, value_low, value_high, force_low, force_high);

  Serial.print("Force from ");
  Serial.print(force_low);
  Serial.print(" to ");
  Serial.print(force_high);
  Serial.print(" : ");
  Serial.println(force);

  return force;
}

/*
 * Tests the load cell value acquisition
 */
void testSensor(){
  int i = 0;
  while(i>=0){
    
    if(Serial.available()){//loop stops if we send a negative value
      String reading = Serial.readString();
      i = reading.toInt();
    }
    
    getForce();
  }
  Serial.println("sensorTest stopped\n\n\n");
}

// control
//-------------------------------------------------------------------
// returns the pwm output rate to send to the ESC
double control(double yc, double y) {

  err = yc - y;

  ui += Ki * Te * err;
  ud = Kd / Te * (err - err_p);

  double u = Kp * (err + ui + ud);

  err_p = err;

  return u;
}

//-------------------------------------------------------------------

//main functions
//-------------------------------------------------------------------
/*
 *  Run the command transmision and the sensor acquisition
 */
void commandProgram(){
 
 int pulse = MIN_PULSE_LENGTH;
 
 while(pulse>=0){ //loop stops if we send a negative value
    if(Serial.available()) pulse = setCommandSerial();
    command(pulse); 
    getForce();
 }
 Serial.println("commandProgram stopped\n\n\n");
}



void controlProgram(){
  int pulse = MIN_PULSE_LENGTH;
  
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
/**
 * Displays instructions to user
 */
void displayInstructions()
{  
    Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
    Serial.println("\t0 : Calibration of the ESC");
    Serial.println("\t1 : Run commandProgram");
    Serial.println("\t2 : Run testCommand function");
    Serial.println("\t3 : Run testSensor function\n\n");
    
}
