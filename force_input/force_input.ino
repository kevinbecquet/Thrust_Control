/*
measuring the force applied to the load cell

accuracy : +- 10^-2 N

potential causes : 
- unstable HX711 alimentation tension : it's more accurate with an external alimentation



*/


#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 11;
const int LOADCELL_SCK_PIN = 10;

HX711 scale;

// Calibrating the load cell
double g = 9.81; // acceleration of Earth's gravity

double value_low = -77695; //output value of the sensor when the motor is unloaded
double force_low = 0; // motor unloaded -> 0N


double value_high = -511700; //output value of the sensor when the motor is loaded by 2kg
double force_high = 2*g; // Force developped by 2kg (F = m*g)


// linear mapping
double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
}

void loop() {

  if (scale.is_ready()) {
      
    double reading = scale.read();
    //Serial.print("Result in unit: ");
    //Serial.print(reading);
    
    double force = map(reading, value_low, value_high, force_low, force_high); 
    Serial.print(" | Result in N: ");
    Serial.println(force,2);

    /*
    double mass = map(reading, value_low, value_high, force_low, force_high/g); 
    Serial.print(" | Result in kg: ");
    Serial.println(mass,4);
    */
    
    scale.wait_ready(0); // wait until the HX711 is ready to read another value
  } 
  
  else {
    Serial.println("HX711 not found.");
    
  }
  
}
