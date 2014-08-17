#include "header.h"
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  initGyro();
  initMagneto();
  initAccel();  
  initMotors();
  delay(2000);
  InitializePID();
  initRX();

  //Set PID tunings and initaize PID variables
  setYawTunings(0,0,0);
  setRollTunings(5,0,0);
  setPitchTunings(5,0,0);
  setOutputLimits(0, 1999);
  setMode(1);
  delay(1000);
  //Prepare quad for flight
  armMotors();

#ifdef DEBUG
  Serial.println("Initalization complete");
#endif
  lasttime = micros();
}

void loop() {
  now = micros();
  dt = (now-lasttime)/1000000;
  calculateMotorValues();
#ifdef DEBUG
//  printGyroVals();
//  printAccelVals();
  printMotorVals();
  printPID();
  Serial.print("Roll: ");
  Serial.println(calcRoll());
  Serial.print("Pitch: ");
  Serial.println(calcPitch());
#endif

  delay(15);
  lasttime = now;

}

