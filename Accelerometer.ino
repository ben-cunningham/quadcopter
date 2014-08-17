#include "Wire.h"

//map float values
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void initAccel(){
  //all values are correctly set from default
}

void calcAccelVals() {
  
  byte* data = readFromDevice(ACCEL, 0x02, 6);
  xRead =  (((data[0] | (data[1] << 8))>>2) / 4096.0) - accelXOffset;
  yRead = (((data[2] | (data[3] << 8))>>2) / 4096.0) - accelYOffset;
  zRead = (((data[4] | (data[5] << 8))>>2) / 4096.0) - accelZOffset;
  //convert readings to angles
  accelVals[0] = RAD_TO_DEG * (atan2(yRead, zRead));
  accelVals[1] = RAD_TO_DEG * (atan2(xRead, sqrt(yRead*yRead + zRead*zRead)));
  accelVals[2] = RAD_TO_DEG * (atan2(-yRead, -xRead) + PI);
}

//return accelerometer values from IMU
float getXAccel() {
 return accelVals[0];
}

float getYAccel() {
  return accelVals[1];
}

float getZAccel() {
  return accelVals[2];
}


void printAccelVals() {
  Serial.println("Accel vals: ");
  Serial.print("x: ");
  Serial.print(getXAccel());
  Serial.print(" y: ");
  Serial.print(getYAccel());
  Serial.print(" z:");
  Serial.print(getZAccel());
  Serial.println();


}
