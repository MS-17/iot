#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

// sketch => include lib => manage libs to install libs above
// WiFi by Arduion 1.2.7
// WiFiEsp by bportaluri 2.2.2


ESP8266WiFiMulti wifiMulti;
WiFiClient wifiClient;
String ip = "ip is not set";
bool AP_MODE_ENABLED = false;


// get mac address to know which net is mine
String id(){
  int mac_len = WL_MAC_ADDR_LENGTH;
  uint8_t mac[mac_len];
  WiFi.softAPmacAddress(mac);
  // get the 2 last symbols of the mac address
  String mac_id = String(mac[mac_len - 2], HEX) + String(mac[mac_len - 1], HEX) + "smn";
  // Serial.println("mac_id " + mac_id);
  return mac_id;
}


// actually here we try to make esp microcontroller a router. When you connect your phone to
// it, it will assign it an ip address automatically (like dhcp server)


// start esp
bool start_AP_mode(){

  // basically this is an esp name which will appear in the wifi settings of your phone
  String ssid_id = AP_NAME + id();

  // set microcontroller ip (10, 192 subnets may be used)
  IPAddress ap_IP(192, 168, 8, 2);
  // disconnect from wifi to configure
  WiFi.disconnect();

  // set mode to hot spot
  AP_MODE_ENABLED = WiFi.mode(WIFI_AP);
  
  WiFi.printDiag(Serial);

  Serial.println("AP_MODE_ENABLED: " + String(AP_MODE_ENABLED));
  // ip settings. set esp ip, router ip (gateway) and subnet mask
  WiFi.softAPConfig(ap_IP, ap_IP, IPAddress(255, 255, 255, 0));
  
  // setup the microcontroller as a hot spot (with name and password). It will appear in your wifi settings with a name = ap_name + id() (+ you need to convert to char* because the method needs chars)
  WiFi.softAP((AP_NAME + id()).c_str(), AP_PASSWORD.c_str());
  
  Serial.println("ap mode ssid: " + ssid_id);
  
  return true;

}


// below we try to connect the esp to the internet (to be more precise, to the hotspot so that we can
// communicate with it passing its local ip address on the computer)

// ap mode makes esp a hotspot itself, so it's not connected to the internet


bool start_client_mode(String cli_ssid=CLI_SSID, String cli_pass=CLI_PASS){
  // Serial.println("Start client mode");
  bool a = wifiMulti.addAP(cli_ssid.c_str(), cli_pass.c_str());
  // Serial.println(String("added:") + String((a ? " ok" : " not ok")));
  
  static int x;  // by default x = 0

  // while not connected try to connect
  while(wifiMulti.run() != WL_CONNECTED){

    // led blink 
    x = x ^ 1;
    digitalWrite(LED_BUILTIN, x);

    delay(10);
  }
  ip = WiFi.localIP().toString();
  Serial.println("ip: " + ip);
  return true;
}


bool init_WIFI(bool AP_mode){
  if(AP_mode){
    start_AP_mode();
    Serial.println("AP mode started");
    ip = WiFi.softAPIP().toString();
    Serial.println("init_wifi() ap_mode, set ip: " + ip);
  } else {
    start_client_mode();
    Serial.println("Client mode started");
    ip = WiFi.localIP().toString();
    Serial.println("init_wifi() client_mode, set ip: " + ip);
  }
  // Serial.println("IP addr = " + ip);
  return true;
}

