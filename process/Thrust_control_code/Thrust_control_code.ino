/**
* Usage, according to documentation(https://www.firediy.fr/files/drone/HW-01-V4.pdf) : 
*     1. Plug your Arduino to your computer with USB cable, open terminal, then type 1 to send max throttle to every ESC to enter programming mode
*     2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK
*     3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed
*     4. Type 0 to send min throttle
*     5. Several "beep" tones emits, which means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo)
*     6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed
*     7. Type 2 to launch test function. This will send min to max throttle to ESCs to test them
*
* @author lobodol <grobodol@gmail.com>
*/

#include <Servo.h>
// ---------------------------------------------------------------------------
// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000// Maximum pulse length in µs
// ---------------------------------------------------------------------------
Servo esc;
char data;
// ---------------------------------------------------------------------------


// Calibrating the load cell
// ---------------------------------------------------------------------------
int sensorPin = 8;

double g = 9.81; // acceleration of Earth's gravity

double value_low = 0; //output value of the sensor when the motor is unloaded
double force_low =0;// -0.5 * g; // Force developped by -0.5kg -> -5 N

double value_high = 1023; //output value of the sensor when the motor is loaded by 2 kg
double force_high = 255;//2.5 * g; // Force developped by 2 kg (F = m*g) -> 24.5 N

//---------------------------------------------------------------------------
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
            case 49 : Serial.println("Enter value between 0 and 100% of the motor speed.");
                      Serial.println("Enter negative value to stop");
                      fStart();
                      testCommand();
                      displayInstructions();
            break;

            //2
            case 50 : Serial.println("Acquisition of the load cell values");
                      Serial.println("Send a negative value to stop the acquisition");
                      fStart();
                      testSensor();
                      displayInstructions();
            
            break;

            //3
            case 51 : 
                      Serial.println("Send values between 0 and 100% to make the motor spin accordingly");
                      Serial.println("Send negative value to make the program stop");
                      fStart();
                      commandProgram();
                      displayInstructions();
                                     
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
 

/*
 * Conversion of the percentage of the speed of the motor in the corresponding pulse length
 */
int setCommand(){

  String reading = Serial.readString();
  float ratio = reading.toInt();
  
  int pulse = map(ratio,0,100,MIN_PULSE_LENGTH,MAX_PULSE_LENGTH);
  
  Serial.print("Ratio value in % = ");
  Serial.println(ratio);
  
  if(ratio < 0) return  -1;
  
  Serial.print("Pulse length = ");
  Serial.println(pulse);
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

/* 
 *  Reads the data output from the AD620 amplifier and converts it in Force (N)
 */
double getForce() {

  double reading = analogRead(sensorPin);

  double force = map(reading, value_low, value_high, force_low, force_high);

  Serial.print("Force 0 to 255: ");
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

/*
 *  Run the command transmision and the sensor acquisition
 */
void commandProgram(){
 
 int pulse = MIN_PULSE_LENGTH;
 
 while(pulse>=0){ //loop stops if we send a negative value
    if(Serial.available()) pulse = setCommand();
    command(pulse); 
    getForce();
 }
 Serial.println("commandProgram stopped\n\n\n");
}

/**
 * Displays instructions to user
 */
void displayInstructions()
{  
    Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
    Serial.println("\t0 : Calibration of the ESC");
    Serial.println("\t1 : Run testCommand function");
    Serial.println("\t2 : Run testSensor function");
    Serial.println("\t3 : Run commandProgram");
}
