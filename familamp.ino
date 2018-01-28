#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <FastLED.h>
 
const char* mqttServer = "m11.cloudmqtt.com";

const char* mqttUser = "xxxxxxxxx";         // CloudMQTT Username
const char* mqttPassword = "xxxxxxxxx";     // CloudMQTT password
const int mqttPort = 11086;
 
WiFiClient espClient;
PubSubClient MQTT(espClient);
 
void setup() {
 
  Serial.begin(115200);
  
  WiFiManager wifiManager; // wifi configuration wizard
  wifiManager.autoConnect("familamp"); // configuration for the access point
  Serial.println("WiFi Client connected!)");

 
  MQTT.setServer(mqttServer, mqttPort); // set MQTT sever and port - CloudMQTT in this case
  MQTT.setCallback(callback);
 
  while (!MQTT.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (MQTT.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(MQTT.state());
      delay(2000);
 
    }
  }
 
  MQTT.publish("FamiLamp", "Hello from familamp");
  MQTT.subscribe("FamiLamp");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  MQTT.loop();
}
