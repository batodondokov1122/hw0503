#include "wifi.h"
#include "Server.h"
#include "MQTT.h"
#include "Range.h"
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  WIFI_init(false);
  server_init();
  MQTT_init();
  init_sensor();
  mqtt_cli.publish((mqtt_client_id +"/state").c_str(), "hello");
  //mqtt_cli.subscribe(sensor_topic);

}

void loop() {
  server.handleClient();
  mqtt_cli.loop();
  float range = get_range();
  mqtt_cli.publish((mqtt_client_id + "/range").c_str(), String(range).c_str());
  delay(1000);
}
