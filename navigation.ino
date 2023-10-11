//PID initials
float  Kp = .085; //values worked: .115, .085 for 60% speed
float Ki = 0.000;  
float  Kd = .078; //values worked: .09, .078 for 60% speed

int P;
int I;
int D;
int lastError = 0;

void Navigate() {


  uint16_t position = qtr.readLineBlack(sensorValues);

  bool detected[6] = {0,0,0,0,0,0}; //for storing IR detectection status
  for (uint8_t i = 0; i < SensorCount; i++) {
    if(sensorValues[i] > 500) detected[i] = 1;
    else detected[i] = 0;
  }

  bool hardLeft = detected[0] && detected[1] && detected[2];
  bool hardRight = detected[3] && detected[4] && detected[5];
  bool crossSection = detected[0] && detected[1] && detected[2] && detected[3] && detected[4] && detected[5];

  if(crossSection) PIDNavigate(position);
  else if(hardLeft) HardLeft();
  else if(hardRight) HardRight();
  else PIDNavigate(position);
}


void PIDNavigate(uint16_t position){
  Serial.println("PID Navigate");
  int error = 2500 - position; //0 - 5000 for 6 IRs thus 2500 
  
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;

  int motorspeed = P*Kp + I*Ki + D*Kd; 

  int leftMotorSpeed = BaseSpeed - motorspeed;
  int rightMotorSpeed = BaseSpeed + motorspeed;

  if (rightMotorSpeed > MaxSpeed) rightMotorSpeed = MaxSpeed;
  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  
  if (leftMotorSpeed > MaxSpeed) leftMotorSpeed = MaxSpeed;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;
  
  Forward(leftMotorSpeed, rightMotorSpeed);
}


void CrossSectionNavigate(bool lineOnCenter){
  Forward(BaseSpeed * 0.5, BaseSpeed * 0.5);
  delay(200);
  if(!lineOnCenter) {
    Serial.println("T Section.");
    Stop(1000);
  }
  else{
    Serial.println("CROSS Section.");
    Forward(BaseSpeed * 0.5, BaseSpeed * 0.5);
    delay(200);
  }
}
