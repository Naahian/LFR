//PID initials
float  Kp = .085; //values worked: .115, .085 for 60% speed
float Ki = 0;  
float  Kd = .078; //values worked: .09, .078 for 60% speed

int P;
int I;
int D;
int lastError = 0;

void Navigate() {
  bool hardLeft = 1;
  bool hardRight = 1;
  bool crossSection = 1;
  bool lineOnCenter = 1;

  uint16_t position = qtr.readLineBlack(sensorValues);
  
  for (uint8_t i = 0; i < SensorCount; i++) {
    // if none of the left 3 IR dosnt detect then no need to turn hard left
    if (i < 3 && !lineDetected(sensorValues[i])) hardLeft = 0;
    // if none of the right 3 IR dosnt detect then no need to turn hard right
    else if (i >= 3 && !lineDetected(sensorValues[i])) hardRight = 0;
    //if any of the ir is not detecting then not a crossSection
    if(!lineDetected(sensorValues[i])) crossSection = 0;
    if((i==2 || i==3) && !lineDetected(sensorValues[i])) lineOnCenter = 0;  
  }

  // if(crossSection) CrossSectionNavigate(lineOnCenter);
  //  if(hardLeft) HardLeft();
  // else if(hardRight) HardRight();
  // else
    PIDNavigate(position);
  
  PIDNavigate(position);
}


void PIDNavigate(uint16_t position){
  Serial.println("PID Navigate");
  int error = 2500 - position; 
  
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

// void SimpleNavigate(uint16_t position) {
//   Serial.println("SimpleNavigate");
//   //positino 0 to 5000 ==> line position LEFT to RIGHT

//   if (position < 400) Forward(BaseSpeed * 0.08, MaxSpeed);
//   else if (position < 1000) Forward(BaseSpeed * 0.15, BaseSpeed * 0.9);
//   else if (position < 1900) Forward(BaseSpeed * 0.45, BaseSpeed * 0.75);
//   else if (position >= 1900 && position <= 3100) Forward(BaseSpeed * 0.7, BaseSpeed * 0.7);
//   else if (position > 3100 && position <= 4000) Forward(BaseSpeed * 0.75, BaseSpeed * 0.45);
//   else if (position > 4000 && position <= 4600) Forward(BaseSpeed * 0.9, BaseSpeed * 0.15);
//   else if (position > 4600) Forward(MaxSpeed, BaseSpeed * 0.08);
// }

void CrossSectionNavigate(bool lineOnCenter){
  Serial.println("CrossSection");
  
  Forward(BaseSpeed * 0.5, BaseSpeed * 0.5);
  delay(150);

  if(!lineOnCenter) {
    Serial.println("T Section.");
    HardLeft();
  }
  else{
    Serial.println("CROSS Section.");
  }}
