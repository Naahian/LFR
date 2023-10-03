void SetupMotor() {
  pinMode(PWM_L, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);

  //set initial speed
  analogWrite(PWM_L, BaseSpeed);
  analogWrite(PWM_R, BaseSpeed);
}


void LeftRotate() {
  analogWrite(PWM_L, 140);
  analogWrite(PWM_R, 140);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorR1, LOW);

  digitalWrite(MotorR2, HIGH);
  digitalWrite(MotorL2, HIGH);

  Serial.println("LeftRotate");
}

void HardLeft() {
  analogWrite(PWM_R, MaxSpeed);
  analogWrite(PWM_L, 0);
  Serial.println("Hard Left");
  
  Stop(100);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorR1, LOW);

  digitalWrite(MotorR2, HIGH);
  digitalWrite(MotorL2, HIGH); 
  delay(300);
  Stop(100);
}



void HardRight() {
  analogWrite(PWM_R, 0);
  analogWrite(PWM_L, MaxSpeed);
  Serial.println("Hard Right");

  Stop(100);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorR1, HIGH); //

  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorL2, LOW);
  delay(300);
  Stop(100);

}

void Forward(uint16_t leftMotorSpeed = BaseSpeed, uint16_t rightMotorSpeed = BaseSpeed) {
  analogWrite(PWM_L, leftMotorSpeed);
  analogWrite(PWM_R, rightMotorSpeed);


  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorR1, LOW);

  digitalWrite(MotorR2, HIGH);
  digitalWrite(MotorL2, LOW);   

  Serial.println("Forward");
}


void Stop(uint16_t Delay) {
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorR1, LOW);

  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorL2, LOW);

  delay(Delay);
  Serial.println("Motors Stopped");
}

void MotorTest() {
  LeftRotate();
}
