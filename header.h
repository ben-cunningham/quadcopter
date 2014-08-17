#define GYRO 0x68
#define GYRO_FS_SEL 03h
#define GYRO_VALS 8
#define G_SMPLRT_DIV 0x15
#define G_DLPF_FS 0x16
#define G_INT_CFG 0x17
#define G_PWR_MGM 0x3E

#define RESET 0x10

#define channelOne 6 //yaw
#define channelTwo 9 //roll
#define channelThree 10 //pitch
#define channelFour 11 //throttle

#define motorOnePin 4
#define motorTwoPin 5
#define motorThreePin 3
#define motorFourPin 6

#define GYRO 0x68
#define ACCEL 0x38
#define RESET 0x10
#define MAGNETO 0x1E

#define MAX_ROLL 50
#define MIN_ROLL -50
#define MAX_PITCH 50
#define MIN_PITCH -50
#define MAX_YAW 360
#define MIN_YAW -360

//#define DEBUG 1

float compRoll, compPitch;
float now, lasttime, dt;

float accelVals[3];
float accelXOffset = 0.14;
float accelYOffset = -0.05;
float accelZOffset = -0.04;
float xRead, yRead, zRead;

float gyroXOffset = -4.3;
float gyroYOffset = -1.4;
float gyroZOffset = -0.7;
float gyroXAngle, gyroYAngle, gyroZAngle;

unsigned long lastTime;
double lastInputYaw, lastInputRoll, lastInputPitch;
double outputYaw, outputRoll;
double outputPitch;
double ITermYaw, ITermPitch,ITermRoll;
double kiYaw, kiPitch, kiRoll;
double kpYaw, kpPitch, kpRoll;
double kdYaw, kdPitch, kdRoll;
int SampleTime = 10;
double outMin, outMax;
bool inAuto = false;
int initYaw;
double targetYaw;
double noYawInput;

