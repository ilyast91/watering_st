/*
   Sensors
*/

void startSensors() {
  Serial.print("Sensors starting: ");
  pinMode(HIGH_SENSOR_PIN, INPUT);
  pinMode(LOW_SENSOR_PIN,  INPUT);
  Serial.println("ok");
}

bool lowSensorIsDown() {
  return digitalRead(LOW_SENSOR_PIN) == LOW;
}

bool highSensorIsDown() {
  return digitalRead(HIGH_SENSOR_PIN) == HIGH;
}
