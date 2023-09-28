void Navigate() {
  uint16_t position = ReadLine();

  bool hardLeft = 1;
  bool hardRight = 1;
  bool crossSection = 1;
  bool lineOnCenter = 1;

  for (uint8_t i = 0; i < SensorCount; i++) {
    // if none of the left 3 IR dosnt detect then no need to turn hard left
    if (i < 3 && sensorValues[i] < 400) hardLeft = 0;
    // if none of the right 3 IR dosnt detect then no need to turn hard right
    else if (i >= 3 && sensorValues[i] < 400) hardRight = 0;
    //if any of the ir is not detecting then not a crossSection
    if(sensorValues[i] < 400) crossSection = 0;
    if((i==2 || i==3) && sensorValues[i] < 400) lineOnCenter = 0;
  }
  
  if(crossSection) CrossSectionNavigate(lineOnCenter);
  else if (hardRight) HardRight();
  else if (hardLeft) HardLeft();
  else SimpleNavigate(position);
    
 
}

void SimpleNavigate(uint16_t position) {
  Serial.println("SimpleNavigate");
  //positino 0 to 5000 ==> line position LEFT to RIGHT

  if (position < 400) Forward(BaseSpeed * 0.1, MaxSpeed);
  else if (position < 1000) Forward(BaseSpeed * 0.15, BaseSpeed * 0.85);
  else if (position < 1900) Forward(BaseSpeed * 0.45, BaseSpeed * 0.7);
  else if (position >= 1900 && position <= 3100) Forward(BaseSpeed * 0.7, BaseSpeed * 0.7);
  else if (position > 3100 && position <= 4000) Forward(BaseSpeed * 0.7, BaseSpeed * 0.45);
  else if (position > 4000 && position <= 4600) Forward(BaseSpeed * 0.85, BaseSpeed * 0.12);
  else if (position > 4600) Forward(MaxSpeed, BaseSpeed * 0.1);
}

void CrossSectionNavigate(bool lineOnCenter){
  Serial.println("CrossSection");
  
  Forward(BaseSpeed * 0.5, BaseSpeed * 0.5);
  delay(150);

  if(!lineOnCenter) {
    Serial.println("Line NOT on CENTER.");
    Stop(150);
    HardLeft();
    delay(440);  
    Stop(100);
  }
  else{
    Serial.println("Line On CENTER.");
  }
}
