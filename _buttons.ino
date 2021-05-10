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
    //todo
    digitalWrite(RESET_PIN, HIGH);
  }
}
