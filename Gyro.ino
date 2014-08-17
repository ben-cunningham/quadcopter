void initGyro()
{
  writeTo(GYRO, 0x3E, 0x80); //send reset to gyro
  writeTo(GYRO, 0x15, 0x00); //sample rate divider
  writeTo(GYRO, 0x16, 0x18); //2000 degree/sec 
  writeTo(GYRO, 0x17, 0x05); //enable send raw values
}

float getXGyro() {
  byte* data = readFromDevice(GYRO, 0x1D, 2);
  float gyroRate = (((data[0] << 8) | data[1]) / 14.375) - gyroXOffset; // divide by 14.375 gives degrees per second
  return gyroRate;
}

float getYGyro() {
  byte* data = readFromDevice(GYRO, 0x1F, 2);
  float gyroRate = (((data[0] << 8) | data[1]) / 14.375) - gyroYOffset; // divide by 14.375 gives degrees per second
  return gyroRate;
}

float getZGyro() {
  byte* data = readFromDevice(GYRO, 0x21, 2);
  float gyroRate = (((data[0] << 8) | data[1]) / 14.375) - gyroZOffset; // divide by 14.375 gives degrees per second
  return gyroRate;
}

void printGyroVals() {
  Serial.println("Gyroscope Values:");
  Serial.print("x: ");
  Serial.print(getXGyro());
  Serial.print(" y: ");
  Serial.print(getYGyro());
  Serial.print(" z: ");
  Serial.print(getZGyro());
  Serial.println();
}
