#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "";

void setup() {

  Serial.begin(9600);

//  Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {

//Getting Data from Arduino via Serial Communication
  String temperature = "";
  String humidity = "";
  while(Serial.available()){
    temperature += (char)Serial.read();
  }

// make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }

  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temperature);
  url+="&field2=";
  url+=String(humidity);
  url+="\r\n";
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    delay(15000);
}
