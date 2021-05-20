/*
   Buttons
*/

void startButtons() {
  Serial.print("Buttons starting: ");
  pinMode(RESET_PIN, INPUT);
  Serial.println("ok");

  checkPressedOnStartSafeModeBtn();
}

void checkPressedOnStartSafeModeBtn() {
  if (digitalRead(RESET_PIN) == HIGH) {
    Serial.println("Starting in SAFE mode");
    safeMode = true;
  }
}

void checkPressedSafeModeBtn() {
  if (digitalRead(RESET_PIN) == HIGH) {
    turnOnRelay(1, HIGH);
    digitalWrite(RESET_PIN, HIGH);
  }
}
