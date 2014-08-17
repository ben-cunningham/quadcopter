#include <Servo.h>

Servo motors[4];
int motorVal[4];
int output;
unsigned long duration;

void initMotors(){
  motors[0].attach(motorOnePin);
  motors[1].attach(motorTwoPin);
  motors[2].attach(motorThreePin);
  motors[3].attach(motorFourPin);
}

void armMotors() {
  int pos;
  //arm the motors
  for(pos = 0; pos < 180; pos += 1) {
    motors[0].write(pos);
    motors[1].write(pos);
    motors[2].write(pos);
    motors[3].write(pos);
  }
  delay(15);
}

void writeToMotors(unsigned long motorSpeed1, unsigned long motorSpeed2, unsigned long motorSpeed3, unsigned long motorSpeed4) {
  motors[0].writeMicroseconds(motorSpeed1);
  motors[1].writeMicroseconds(motorSpeed2);
  motors[2].writeMicroseconds(motorSpeed3);
  motors[3].writeMicroseconds(motorSpeed4);
}

void shutOffMotors() {
  motors[0].detach();
  motors[1].detach();
  motors[2].detach();
  motors[3].detach();
}

void calculateMotorValues() {
  calcAccelVals();
  computePID(); 
  //Need to get all different channels and combine them with PID
  //Base microsecond value that the quadcopter hovers at: 1500 (CONFIRM!)
  int base = 1500;
  //Influence of the throttle on base
  int throttle = 0.7 * (getThrottle() - 1500.0); //1500 value should be mid, possibly map val? 
  
  motorVal[0] = base + throttle + outputPitch + outputYaw;
  motorVal[1] = base + throttle + outputRoll - outputYaw;
  motorVal[2] = base + throttle - outputPitch + outputYaw;
  motorVal[3] = base + throttle - outputRoll - outputYaw;
  
  //Motors stop spinning if send value over 2000
  motorVal[0] = constrain(motorVal[0], 1000, 2000);
  motorVal[1] = constrain(motorVal[1], 1000, 2000);
  motorVal[2] = constrain(motorVal[2], 1000, 2000);
  motorVal[3] = constrain(motorVal[3], 1000, 2000);
  
  writeToMotors(motorVal[0],motorVal[1],motorVal[2],motorVal[3]);
}

void printMotorVals() {
  Serial.print("1: ");
  Serial.println(motorVal[0]);
  Serial.print("2: ");
  Serial.println(motorVal[1]);
  Serial.print("3: ");
  Serial.println(motorVal[2]);
  Serial.print("4: ");
  Serial.println(motorVal[3]);

}
