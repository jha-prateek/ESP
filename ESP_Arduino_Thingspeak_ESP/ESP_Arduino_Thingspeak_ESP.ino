#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "";

void setup() {

  Serial.begin(9600);

// Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
<<<<<<< HEAD
  
// Getting Data from Arduino via Serial Communication
  String data = "";

//Getting Data from Arduino via Serial Communication
  String temperature = "";
  String humidity = "";
>>>>>>> f7cc22309f95cc48c9a4e5b49c68f567883c7143
  while(Serial.available()){
    data += (char)Serial.read();
  }

  String temp = "";
  temp += data[0];
  temp += data[1];

  String humid = "";
  humid += data[2];
  humid += data[3];
  
// make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }

  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temp);
  url+="&field2=";
  url+=String(humid);
  url+="\r\n";
  
// Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(15000);
}
