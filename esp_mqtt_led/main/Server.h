#include <ESP8266WebServer.h>


// make esp a web server
ESP8266WebServer server(WEB_SERVER_PORT);
bool MQTT_ENABLED = false;


void handle_root(){
  String page_code = "<form action=\"/network\" method=\"POST\">";
  page_code +=
    "<input type=\"text\" name=\"login\" value=\"login\"><br>"
    "<input type=\"text\" name=\"password\" value=\"password\"><br>" 
    "<input type=\"submit\" name=\"submit\" value=\"Submit\"></form>";
  server.send(200, "text/html", page_code);
  Serial.println("page code: " + page_code);
  Serial.println("handle / done");
}


void handle_network(){
  Serial.println(String("Handling network endpoint"));
  String cli_ssid;
  String cli_pass;
  for (int i = 0; i < server.args(); i++){
    if (server.argName(i) == "login"){
      cli_ssid = server.arg(i);
    } else if (server.argName(i) == "password"){
      cli_pass = server.arg(i);
    }
  }
  
  Serial.println("login: " + cli_ssid + " password: " + cli_pass);
  
  if(server.args()){
    server.send(200, "text/html", "Your data was received");
    Serial.println("Starting client mode");
    bool client_mode_enabled = start_client_mode(cli_ssid, cli_pass);
    if (client_mode_enabled) {
      Serial.println("Stopping ap mode");
      // https://arduino.stackexchange.com/questions/54372/how-to-turn-off-or-stop-access-point-network-in-esp8266
      if(WiFi.softAPdisconnect()){
        AP_MODE_ENABLED = false;  // see this global variable in WiFi.h
      }
      Serial.println("Client mode started successfully");
      Serial.println("Initializing mqtt");
      MQTT_ENABLED = init_MQTT();   // see this global variable initialization in this file
      Serial.println("mqtt_enabled: " + String(MQTT_ENABLED));
    }
  }
}


void handle_not_found(){
  server.send(404, "text/html", "404: Check url");
}


// register handlers for endpoints
void server_init(){
  Serial.println("server init entry");
  server.on("/", HTTP_GET, handle_root);

  server.on("/network", HTTP_POST, handle_network);
  // server.on("/sensor", HTTP_GET, handle_sensor);

  server.onNotFound(handle_not_found);
  server.begin();
  Serial.println("Server has started on port " + String(WEB_SERVER_PORT) + " Enjoy)");
}

