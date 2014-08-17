#define MANUAL 0
#define AUTOMATIC 1

void computePID() {
  //ASSIGN VARIABLES TO GETTERS INSTEAD OF CALLING MULTIPLE TIMES
  
  if(!inAuto) return;
  unsigned long now = millis();
  int timeChange = (now - lastTime);
  //if joystick is centered, no movement along z axis
  if(getYaw() <= 1470 && getYaw() >= 1420) {
      targetYaw = noYawInput;
  } 
  else {
    targetYaw = map(getYaw(), 1000, 2000, MIN_YAW, MAX_YAW) + targetYaw;
    noYawInput = targetYaw;
  }
  double targetPitch = map(getPitch(), 1000, 2000, MIN_PITCH, MAX_PITCH);
  double targetRoll = map(getRoll(), 1000, 2000, MIN_ROLL, MAX_ROLL);
    
  //if joystick is centered along y and x axis, hover parallel to ground
  if(getRoll() <= 1470 && getRoll() >= 1420) targetPitch = 0;
  if(getPitch() <= 1470 && getPitch() >= 1420) targetPitch = 0;
 
  double errorYaw = targetYaw - calcYaw();
  double errorPitch = targetPitch - calcPitch();
  double errorRoll = targetRoll - calcRoll();
  
  ITermYaw += (kiYaw * errorYaw);
  ITermPitch += (kiPitch * errorPitch);
  ITermRoll += (kiRoll * errorRoll);
  
  //Only start comuting integral once quad is flying
  if(getThrottle() < 1200) {
    ITermYaw = 0;
    ITermPitch = 0;
    ITermRoll = 0;
  }

  double dYaw = (targetYaw - lastInputYaw);
  double dPitch = (targetPitch - lastInputPitch);
  double dRoll = (targetRoll - lastInputRoll);

  //Compute PID
  outputYaw = kpYaw * errorYaw + ITermYaw * kiYaw + kdYaw * dYaw; 
  outputPitch = kpPitch * errorPitch + kiPitch * ITermPitch + kdPitch * dPitch;
  outputRoll = kpRoll * errorRoll + kiRoll * ITermRoll + kdRoll * dRoll; 

  lastInputYaw = targetYaw;
  lastInputRoll = targetRoll;
  lastInputPitch = targetPitch;
  lastTime = now;
}

void setYawTunings(double Kp, double Ki, double Kd) {
  double SampleTimeInSec = ((double)SampleTime)/1000;

  kpYaw = Kp;
  kiYaw = Ki *SampleTimeInSec;
  kdYaw = Kd / SampleTimeInSec;
}

void setPitchTunings(double Kp, double Ki, double Kd) {
  double SampleTimeInSec = ((double)SampleTime)/1000;

  kpPitch = Kp;
  kiPitch = Ki *SampleTimeInSec;
  kdPitch = Kd / SampleTimeInSec;
}

void setRollTunings(double Kp, double Ki, double Kd) {
  double SampleTimeInSec = ((double)SampleTime)/1000;

  kpRoll = Kp;
  kiRoll = Ki *SampleTimeInSec;
  kdRoll = Kd / SampleTimeInSec;
}

void setOutputLimits(double Min, double Max) {
  if(Min > Max) return;
  outMin = Min;
  outMax = Max;

  outputYaw = constrain(outputRoll, outMin, outMax);
  outputPitch = constrain(outputRoll, outMin, outMax);
  outputRoll = constrain(outputRoll, outMin, outMax);

  ITermYaw = constrain(ITermYaw, outMin, outMax);
  ITermPitch = constrain(ITermPitch, outMin, outMax);
  ITermRoll = constrain(ITermRoll, outMin, outMax);
}

void setMode(int mode) {
  bool newAuto = (mode == AUTOMATIC);
  if(newAuto == !inAuto) {
    InitializePID();
  }
  inAuto = newAuto;
}

void InitializePID() {
  initYaw = calcYaw();
  targetYaw = initYaw;
  noYawInput = initYaw;
  lastInputYaw = initYaw;
  lastInputRoll = map(getRoll(), 1000, 2000, MIN_ROLL, MAX_ROLL);
  lastInputPitch = map(getPitch(), 1000, 2000, MIN_PITCH, MAX_PITCH);
  
  
  ITermYaw = outputYaw;
  ITermPitch = outputPitch;
  ITermRoll = outputRoll;
  ITermYaw = constrain(ITermYaw, outMin, outMax);
  ITermPitch = constrain(ITermPitch, outMin, outMax);
  ITermRoll = constrain(ITermRoll, outMin, outMax);
}

void printPID() {
  Serial.print("Throttle: ");
  Serial.println(getThrottle());
  Serial.print("PID roll: ");
  Serial.println(outputRoll);
  Serial.print("PID pitch: ");
  Serial.println(outputPitch);
  Serial.print("PID Yaw: ");
  Serial.println(outputYaw);
}

