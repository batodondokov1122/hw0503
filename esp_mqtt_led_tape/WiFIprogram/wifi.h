#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
WiFiClient wifiClient;

String ip = "IP address";
String AP_PASSWORD = "121212";
String ssidCLI = "Sukpzdc";
String passwordCLI = "qpbr1561";

String id(){
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 2], HEX);
  macID.toUpperCase();
  return macID;
}

bool StartAPMode(){
  IPAddress apIP(192, 168, 128, 1);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("ESP8266_" + id(), "");
  Serial.println("Wifi up in AP mode: ESP8266_" + id());
  return true;
}

bool StartCLIMode(){
  wifiMulti.addAP(ssidCLI.c_str(), passwordCLI.c_str());
  while(wifiMulti.run() != WL_CONNECTED){
  }
  Serial.println("Wifi client is UP");
  return true;
}

void WIFI_init(bool ap_mode){
  if(ap_mode){
    StartAPMode();
    ip = WiFi.softAPIP().toString();
  }else{
    StartCLIMode();
    ip = WiFi.localIP().toString();
  }
  Serial.println("IP address:" + ip);
}