/*
   Settings
*/

const String settings_prefix = "/settings_";
const String settings_suffix = ".json";

void startFsSettings() {
  Serial.print("FsSettings starting: ");
  if (SPIFFS.begin()) {
    if (safeMode) {
      SPIFFS.format();
      Serial.println("FsSettings flash formatted");
    }
    readWifiSettings();
    Serial.println("ok");
  } else {
    Serial.println("failed");
    delay(1000);
    ESP.restart();
  }
}

/*
  Wifi Settings
*/
struct Settings_wifi {
  String wifi_start_sta;
  String wifi_ssid;
  String wifi_password;
} wifiSettings;

bool readWifiSettings() {
  File file = SPIFFS.open(settings_prefix + "wifi" + settings_suffix, "r");
  String settings = file.readString();
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, settings);
  if (error) return false;

  wifiSettings.wifi_start_sta = doc["wifi_start_sta"].as<String>();
  wifiSettings.wifi_ssid = doc["wifi_ssid"].as<String>();
  wifiSettings.wifi_password = doc["wifi_password"].as<String>();
  
  return true;
}

bool writeWifiSettings() {
  DynamicJsonDocument doc(1024);
  doc["wifi_start_sta"] = wifiSettings.wifi_start_sta;
  doc["wifi_ssid"] = wifiSettings.wifi_ssid;
  doc["wifi_password"] = wifiSettings.wifi_password;
  
  File file = SPIFFS.open(settings_prefix + "wifi" + settings_suffix, "w");
  bool result = serializeJson(doc, file);
  file.close();
  return result;
}
