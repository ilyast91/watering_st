/*
   WebServer
*/
void startWebServer() {
  Serial.print("WebServer starting: ");
  server.on("/", HTTP_GET, handle_Root);  
 
  server.on("/settings_relay", HTTP_GET, handle_settings_relay_get);
  server.on("/settings_relay", HTTP_POST, handle_settings_relay_post);  
  server.on("/settings_wifi", HTTP_GET, handle_settings_wifi_get);
  server.on("/settings_wifi", HTTP_POST, handle_settings_wifi_post);
  
  server.on("/restart", HTTP_GET, handle_restart);
  server.onNotFound(handle_notFound);

  server.begin();
  Serial.println("ok");
}

void webServerLooping() {
  server.handleClient();
}

/*
   Endpoints
*/
void handle_Root()
{
  String handle_Root_response;

  handle_Root_response += "<div class=\"row\">";
   
  // card
  handle_Root_response += "<div class=\"col-xl-4 col-lg-6 col-sm-12\">";
  handle_Root_response += "<div class=\"card m-3\"><div class=\"card-body\">";
  handle_Root_response += "<h5 class=\"card-title\">Датчики</h5><p class=\"card-text\">";
  handle_Root_response += "Верхний уровень: " + String(readSensor("high")) + "</br>";
  handle_Root_response += "Нижний уровень: " + String(readSensor("low")) + "</br>";
  handle_Root_response += "</br>";
  handle_Root_response += "</p></div></div>";
  handle_Root_response += "</div>";
  
  // card
  handle_Root_response += "<div class=\"col-xl-4 col-lg-6 col-sm-12\">";
  handle_Root_response += "<div class=\"card m-3\"><div class=\"card-body\">";
  handle_Root_response += "<h5 class=\"card-title\">Реле</h5><p class=\"card-text\">";
  handle_Root_response += "Реле Наполнения: " + relayStatus.relay_1 + "</br>";
  handle_Root_response += "Реле Полива 1: " + relayStatus.relay_2 + "</br>";
  handle_Root_response += "Реле Полива 2: " + relayStatus.relay_3 + "</br>";
  handle_Root_response += "Реле Полива 3: " + relayStatus.relay_4 + "</br>";
  handle_Root_response += "</br>";
  handle_Root_response += "</p></div></div>";
  handle_Root_response += "</div>";
   
  // card
  handle_Root_response += "<div class=\"col-xl-4 col-lg-6 col-sm-12\">";
  handle_Root_response += "<div class=\"card m-3\"><div class=\"card-body\">";
  handle_Root_response += "<h5 class=\"card-title\">Информация о плате</h5>";
  handle_Root_response += "<p class=\"card-text\"><table class=\"table table-sm table-hover table-bordered\"><tbody>";  
  handle_Root_response += "<tr><td><strong>Vcc</strong></td><td>"+String(ESP.getVcc())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FreeHeap</strong></td><td>"+String(ESP.getFreeHeap())+"</td></tr>";  
  handle_Root_response += "<tr><td><strong>ChipId</strong></td><td>"+String(ESP.getChipId())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>SdkVersion</strong></td><td>"+String(ESP.getSdkVersion())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>BootVersion</strong></td><td>"+String(ESP.getBootVersion())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>BootMode</strong></td><td>"+String(ESP.getBootMode())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>CpuFreqMHz</strong></td><td>"+String(ESP.getCpuFreqMHz())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FlashChipId</strong></td><td>"+String(ESP.getFlashChipId())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FlashChipRealSize</strong></td><td>"+String(ESP.getFlashChipRealSize())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FlashChipSpeed</strong></td><td>"+String(ESP.getFlashChipSpeed())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FlashChipMode</strong></td><td>"+String(ESP.getFlashChipMode())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FlashChipSizeByChipId</strong></td><td>"+String(ESP.getFlashChipSizeByChipId())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>SketchSize</strong></td><td>"+String(ESP.getSketchSize())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>FreeSketchSpace</strong></td><td>"+String(ESP.getFreeSketchSpace())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>ResetInfo</strong></td><td>"+String(ESP.getResetInfo())+"</td></tr>";
  handle_Root_response += "<tr><td><strong>CycleCount</strong></td><td>"+String(ESP.getCycleCount())+"</td></tr>";
  handle_Root_response += "</tbody></table></p>";
  handle_Root_response += "</div></div>";
  handle_Root_response += "</div>";
  
  handle_Root_response += "</div>";
  
  sendHTML(200, handle_Root_response);
}

/*
  Relay Settings
*/
void handle_settings_relay_get() {

  String settings_form;
  settings_form += "<form method=\"post\"><legend>Изменение уровня реле</legend>";
  settings_form += createYesNoSelect("relay_1", "Реле 1", relayStatus.relay_1);  
  settings_form += createYesNoSelect("relay_2", "Реле 2", relayStatus.relay_2);  
  settings_form += createYesNoSelect("relay_3", "Реле 3", relayStatus.relay_3);  
  settings_form += createYesNoSelect("relay_4", "Реле 4", relayStatus.relay_4);  
  settings_form += "<button type=\"submit\" class=\"btn btn-primary mx-1\">Изменить</button>";
  settings_form += "</form>";

  sendHTML(200, "Сенсоры", settings_form);
}

void handle_settings_relay_post() {
  String relay_1 = server.arg("relay_1");
  String relay_2 = server.arg("relay_2");
  String relay_3 = server.arg("relay_3");
  String relay_4 = server.arg("relay_4");  

  if (relay_1 != relayStatus.relay_1) turnOnRelay(1, relay_1 == "true" ? HIGH : LOW);
  if (relay_2 != relayStatus.relay_2) turnOnRelay(2, relay_2 == "true" ? HIGH : LOW);
  if (relay_3 != relayStatus.relay_3) turnOnRelay(3, relay_3 == "true" ? HIGH : LOW);
  if (relay_4 != relayStatus.relay_4) turnOnRelay(4, relay_4 == "true" ? HIGH : LOW);
  
  server.sendHeader("Location", String("/settings_relay"), true);
  server.send(302, "text/plain", "");
}

/*
  Wifi Settings
*/
void handle_settings_wifi_get() {

  String settings_form;
  settings_form += "<form method=\"post\"><legend>Изменение настроек WIFI</legend>";
  settings_form += createYesNoSelect("wifi_start_sta", "Wifi mode (Да - SPA, Нет - AP)", wifiSettings.wifi_start_sta);  
  settings_form += createFormTextElement("wifi_ssid", "SSID", wifiSettings.wifi_ssid);
  settings_form += createFormTextElement("wifi_password", "Password", wifiSettings.wifi_password);
  settings_form += "<button type=\"submit\" class=\"btn btn-primary mx-1\">Изменить</button>";
  settings_form += "</form>";

  sendHTML(200, "WIFI", settings_form);
}

void handle_settings_wifi_post() {
  wifiSettings.wifi_start_sta = server.arg("wifi_start_sta");
  wifiSettings.wifi_ssid = server.arg("wifi_ssid");
  wifiSettings.wifi_password = server.arg("wifi_password");
  if (!writeWifiSettings()) {
    sendHTML(200, "<div class=\"alert alert-danger\" role=\"alert\">Ошибка обновления настроек</div>");
  }
  server.sendHeader("Location", String("/settings_wifi"), true);
  server.send(302, "text/plain", "");
}

/*
  Common
*/
void handle_restart() {
  sendHTML(200, "Перезагрузка", "Выполнено <br> Устройство перезагрузится в течении нескольких секунд.");
  delay(3000);
  ESP.restart();
}

void handle_notFound() {
  sendHTML(404, "Страница не найдена");
}
