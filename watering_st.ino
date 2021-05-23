/*
   Watering ST
*/

#include <FS.h>
#include <ArduinoJson.h> // ArduinoJson
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*
   PIN configurations
*/
#define RESET_PIN D0       // RESET
#define HIGH_SENSOR_PIN D1 // HIGH
#define LOW_SENSOR_PIN D2  // LOW
#define RELAY_1_PIN D5     // NAPOLNENIE
#define RELAY_2_PIN D6     // POLIV 1
#define RELAY_3_PIN D7     // POLIV 2
#define RELAY_4_PIN D8     // POLIV 3

#define WEB_SERVER_PORT 80

ESP8266WebServer server(WEB_SERVER_PORT);

bool safeMode = false;

/*
   Initialization
*/
void setup() {
  Serial.begin(9600);
  Serial.setDebugOutput(false);
  Serial.println("\nStarting");
  startButtons();
  startFsSettings();
  startWiFi();
  startWebServer();
  startSensors();
  startRelay();
}

/*
   Loop
*/
void loop() {
  webServerLooping();
  checkPressedSafeModeBtn();
  relayLooping();
}
