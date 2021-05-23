/*
   Relay
*/

struct Relay_status {
  String relay_1;
  String relay_2;
  String relay_3;
  String relay_4;
} relayStatus;

void startRelay() {
  Serial.print("Relay starting: ");
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
  pinMode(RELAY_4_PIN, OUTPUT);

  turnOnRelay(1, LOW);
  turnOnRelay(2, LOW);
  turnOnRelay(3, LOW);
  turnOnRelay(4, LOW);
  Serial.println("ok");
}

void relayLooping() {
  if (safeMode) return;
  if (highSensorIsDown() && lowSensorIsDown()) {
    // Если верхний и нижний датчик true - то набираем воду
    turnOnRelay(1, HIGH);
  } else if (!highSensorIsDown() && !lowSensorIsDown()) {
    // Если верхний и нижний датчик false - то выключаем набор воду
    turnOnRelay(1, LOW);
  } 
}

void turnOnRelay(int pin, bool state) {
  if (pin < 1 || pin > 4) return;
  String state_str = state ? "true" : "false"; 
  
  int relay = 1;
  switch(pin) {
    case 1:
      relay = RELAY_1_PIN;
      relayStatus.relay_1 = state_str;
      break;
    case 2:
      relay = RELAY_2_PIN;
      relayStatus.relay_2 = state_str;
      break;
    case 3:
      relay = RELAY_3_PIN;
      relayStatus.relay_3 = state_str;
      break;
    case 4:
      relay = RELAY_4_PIN;
      relayStatus.relay_4 = state_str;
      break;
  }

  //Serial.println("Relay "+ String(pin) + " state: " + state_str);
  digitalWrite(relay, state);
}
