#include <SoftwareSerial.h>
#include <stdlib.h>
#include <SimpleDHT.h>

/*
  This code is designed to upload Temperature DATA to ThingSpeak 
  DHT -> ArduinoRead -> ESP -> Thingspeak
  ---------------------------
  Connections: ESP
  ESP VCC-3.3v
  ESP TX - 2
  ESP RX - 3
  ESP GND - GND
  ESP GPIO0 - GND
  ESP CH_PD - 3.3v
*S

int pinDHT11 = 4;
SimpleDHT11 dht11;

// replace with your channel's thingspeak API key
String apiKey = "";

SoftwareSerial esp8266(2,3); // 2 TX-TX, 3 RX-RX, CH_PD-VCC

void setup() {                
  Serial.begin(9600);
  esp8266.begin(9600); 

  // reset ESP8266
  esp8266.println("AT+RST");
}


void loop() {

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  Serial.print("Temperature - ");
  Serial.print((int)temperature); 
  Serial.print("*C || "); 
  Serial.print("Humidity - ");
  Serial.print((int)humidity); 
  Serial.println("%");
  // DHT11 sampling rate is 1HZ.
  delay(200);

  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  esp8266.println(cmd);

  if(esp8266.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(temperature);
  getStr +="&field2=";
  getStr += String(humidity);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  esp8266.println(cmd);

  if(esp8266.find(">")){
    esp8266.print(getStr);
  }
  else{
    esp8266.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }

  // thingspeak needs 15 sec delay between updates
  delay(60000);  
}
