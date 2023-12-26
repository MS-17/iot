#include "Config.h"
#include "WiFi.h"
#include "Mqtt.h"
#include "Server.h"


void setup() {
  Serial.begin(9600);
  Serial.println("\n\n\rAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA STARTING CONTROLLER\n\n");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  init_WIFI(true);
  if (AP_MODE_ENABLED){
    server_init();
  }
}

bool MQTT_SUBSCRIBED = false;

void loop() {

  // listen to user requests and process them as they come
  server.handleClient();
  
  if (WiFi.status() != WL_CONNECTED && !AP_MODE_ENABLED){
    Serial.println("Disconnected from wifi, restarting in ap mode");
    Serial.println(WiFi.status() != WL_CONNECTED);
    start_AP_mode();
    MQTT_SUBSCRIBED = false;
  
    WiFi.printDiag(Serial);

  }
  
  if (!MQTT_SUBSCRIBED && MQTT_ENABLED && !AP_MODE_ENABLED && WiFi.status() == WL_CONNECTED){

    String topic = "esp8266_smn_from_isu/led";
    
    // subscribe to the topic
    Serial.println(String("Subscribing to the topic ") + topic);
    MQTT_SUBSCRIBED = mqtt_client.subscribe(topic.c_str());

    WiFi.printDiag(Serial);

    Serial.println(String("MQTT_SUBSCRIBED: ") + String(MQTT_SUBSCRIBED));
    Serial.println("MQTT client status " + String(mqtt_client.state()));    
  
  }

  if(!AP_MODE_ENABLED && !mqtt_client.connected()){
   
    // reconect to mqtt
    Serial.println("mqtt connection was lost, trying to reconnect");
    
    WiFi.printDiag(Serial);
    
    MQTT_ENABLED = init_MQTT();
    MQTT_SUBSCRIBED = false;
    Serial.println("MQTT_ENABLED: " + String(MQTT_ENABLED));
  
  }

  mqtt_client.loop();
  delay(1);
}
