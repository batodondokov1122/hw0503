#include <PubSubClient.h>

PubSubClient mqtt_cli(wifiClient);

String mqtt_brocker = "broker.emqx.io";
int mqtt_port = 1883;
String mqtt_client_id = "esp8266";


void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message recieved on topic:");
  Serial.println(topic);
  Serial.print("Message:");
  for(int i = 0; i < length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println();
    Serial.println("------------------");
}

void MQTT_init(){
  mqtt_cli.setServer(mqtt_brocker.c_str(), mqtt_port);
  while(!mqtt_cli.connected()){
    mqtt_client_id = "esp8266-" + id();
    Serial.print(mqtt_client_id);
    Serial.print("connecting...");
    String client_id = "esp8266-" + String(WiFi.macAddress());
    if(mqtt_cli.connect(client_id.c_str())){
      Serial.println("MQTT connected with id" + client_id);
    }else{
      Serial.println("MQTT failed to connect");
      Serial.println(mqtt_cli.state());
      delay(1000);
    }
  }
}
