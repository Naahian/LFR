//positino 0 to 5000 ==> line position LEFT to RIGHT

void Navigate() {
  uint16_t position = ReadLine();

  bool hardLeft = 1;
  bool hardRight = 1;

  for (uint8_t i = 0; i < SensorCount; i++) {
    // if none of the left 3 IR dosnt detect then no need to turn hard left
    if (i < 3 && sensorValues[i] < 400) hardLeft = 0;
    // if none of the right 3 IR dosnt detect then no need to turn hard right
    else if (i >= 3 && sensorValues[i] < 400) hardRight = 0;
  }

  //45deg condition (it cannot turn porperly)
  // 90deg a bit short turn (turns bit too much)

  if (hardRight) {3
    Serial.println("HardRight");
    Stop(130);
    HardRight();
    delay(455);  //500
    Stop(110);
  } else if (hardLeft) {
    Serial.println("HardLeft");
    Stop(130);
    HardLeft();
    delay(455);  //500
    Stop(110);
  } else {
    SimpleNavigate(position);
    Serial.println("SimpleNavigate");
    // Serial.println("PIDNavigate");
  }
}

void SimpleNavigate(uint16_t position) {
  if (position < 400) Forward(BaseSpeed * 0.1, MaxSpeed);
  else if (position < 1000) Forward(BaseSpeed * 0.15, BaseSpeed * 0.85);
  else if (position < 1900) Forward(BaseSpeed * 0.45, BaseSpeed * 0.7);
  else if (position >= 1900 && position <= 3100) Forward(BaseSpeed * 0.7, BaseSpeed * 0.7);
  else if (position > 3100 && position <= 4000) Forward(BaseSpeed * 0.7, BaseSpeed * 0.45);
  else if (position > 4000 && position <= 4600) Forward(BaseSpeed * 0.85, BaseSpeed * 0.12);
  else if (position > 4600) Forward(MaxSpeed, BaseSpeed * 0.1);
}
