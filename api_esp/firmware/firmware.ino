/**
   PostHTTPClient.ino

    Created on: 21.11.2016

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/
//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "192.168.224.14:4000"

// bad practice, better:
// https://forum.arduino.cc/t/which-option-is-better-define-stassid-stapsk-or-const-char-ssid-password/1113980/6
#ifndef STASSID
#define STASSID "smn"
#define STAPSK "aeaw65500"
#endif


String DEVICE_ID = "esp_device_id";
String LOCATION = "irkutsk";


void setup() {

  Serial.begin(115200);
  Serial.println("Program start");
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  delay(2000);
  Serial.println("Setup complete");
}


void loop() {
  if(Serial.available()){
    String cmd = Serial.readString();
    char c = cmd.charAt(0);
    if(isdigit(c)) {
      Serial.println("User post request: " + cmd + "\nStarting a post procedure");
      post(cmd.toFloat());
    } else if (c == 'g') {
      JsonDocument data = getData();
      Serial.println("Average: " + String(avg(data)));
    } else {
      Serial.println("Unknown command");
    }
  }
}


float avg(JsonDocument data) {
  int length = data["values"].size();
  float avg = 0;
  for (int i = 0; i < length; i++) {
    avg += float(data["values"][i]);
  }
  if (length != 0) {
    avg /= length;
  }
  return avg;
}


JsonDocument getData() {
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    http.begin(client, "http://" + String(SERVER_IP) + "/data/temperature/" + LOCATION);
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");

        JsonDocument data;
        DeserializationError err = deserializeJson(data, payload);

        http.end();
        return data;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  return JsonDocument();
  //delay(10000);
}


void post(float value) {
  Serial.print("Trying to post data");
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" + String(SERVER_IP) + "/data/temperature");  // HTTP
    http.addHeader("Content-Type", "application/json");

    JsonDocument data;
    data["device_id"] = DEVICE_ID;
    data["location"] = LOCATION;
    data["value"] = value;
    String stringData;
    serializeJson(data, stringData);

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST(stringData);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  //delay(10000);
}
