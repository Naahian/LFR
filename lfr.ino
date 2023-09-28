#include <QTRSensors.h>

//motor pins
#define PWM_L 5
#define MotorL1 4
#define MotorL2 3
#define PWM_R 6
#define MotorR1 7
#define MotorR2 8

//motor speed
#define BaseSpeed 255 * 0.65
#define MaxSpeed 255 * 0.75

//Sensor initial
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];


//***************************************************************
void setup() {
  Serial.begin(9600);
  SetupMotor();
  SetupQTR();

  LeftRotate();
  Calibrate();
  Stop(3000);
}


void loop() {
  Navigate();
  delay(8);
}
