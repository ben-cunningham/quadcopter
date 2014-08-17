#include <Wire.h>
#include <HMC5883L.h>
HMC5883L compass;
int error = 0;

void initMagneto() {
  Wire.begin(); // Start the I2C interface.
  compass = HMC5883L();
  error = compass.SetScale(1.3);
  if(error != 0){ // If there is an error, print it out. 
    Serial.println(compass.GetErrorText(error));
    error = 0;
  }
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) {// If there is an error, print it out.
    Serial.println(compass.GetErrorText(error)); //Todo: Error handling for this method in .h and .cpp
    error=0;
  }
}


float getXMagneto() {
  byte* data = readFromDevice(MAGNETO, 0x03, 2);
  return ((data[0] << 8) | data[1]);
}

float getYMagneto() {
  byte* data = readFromDevice(MAGNETO, 0x07, 2);
  return ((data[0] << 8) | data[1]);

}

float getZMagneto() {
  byte* data = readFromDevice(MAGNETO, 0x05, 2);
  return ((data[0] << 8) | data[1]);
}

float calcHeadingInDegrees() {
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  int MilliGauss_OnThe_XAxis = scaled.XAxis;
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  float declinationAngle = 0.0404;
  heading += declinationAngle;
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;

  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
    
  float headingDegrees = heading * 180/M_PI; 
  
  return headingDegrees;
}
