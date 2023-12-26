#include <PubSubClient.h>

// install lib pubsubclient by Nick O'Leary

PubSubClient mqtt_client(wifiClient);
String message = "";

void sendCallback(char *topic, byte *payload, unsigned int length){
  Serial.println("a message from the topic has come");
  Serial.println(topic);
  Serial.println("Message: ");
  for (int i = 0; i < length; i++){
    Serial.print((char) payload[i]);
    message += String((char)payload[i]);
  }
  Serial.println("String message: " + message);
  
  if (message == "on") {
    digitalWrite(LED_BUILTIN, LOW);
    message = "";
  }
  if (message == "off") {
    digitalWrite(LED_BUILTIN, HIGH);
    message = "";
  }
  
  Serial.println();
}


bool init_MQTT(){
  
  Serial.println("Function init mqtt");

  // connect to a broker (the 1 and 2 arg are taken from Config.h)
  mqtt_client.setServer(mqtt_broker, mqtt_port); 
  
  // messages handler
  mqtt_client.setCallback(sendCallback);

  // do while not connected
  while(!mqtt_client.connected()){
    // mqtt_client.setKeepAlive(60);
    String client_id = "esp8266_" + id(); // get id() from WiFi.h

    if(mqtt_client.connect(client_id.c_str())){
      Serial.println("mqtt connected with id = " + client_id);
    } else {
      Serial.println("Trying to connect to the broker");
      delay(500);
    }
  }
  return true;  
}


