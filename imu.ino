//y axis
double calcPitch() {
  compPitch = (0.95 * (compPitch + (getYGyro() * dt))) + (0.05 * getYAccel()); //compute integral and use complementary filter to obtain roll
  return compPitch;
}

//x axis
double calcRoll(){
  compRoll = (0.95 * (compRoll + (getXGyro() * dt))) + (0.05 * getXAccel()); //compute integral and use complementary filter to obtain roll
  return compRoll;
}


double calcYaw(){
  return calcHeadingInDegrees();
}

//write to i2c device
void writeTo(int DEVICE, byte address, byte val) {
  Wire.beginTransmission(DEVICE); //start transmission to ACC 
  Wire.write(address);        // send register address
  Wire.write(val);        // send value to write
  Wire.endTransmission(); //end transmission
}

//read from i2c device
byte *readFromDevice(int device, byte address, int index){
  byte data[index];
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();
  int i = 0;
  Wire.beginTransmission(device);
  Wire.requestFrom(device, index);
  while(Wire.available()) {
    data[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  return data;
}
