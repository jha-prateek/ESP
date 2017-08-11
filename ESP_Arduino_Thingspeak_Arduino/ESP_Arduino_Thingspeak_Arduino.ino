#include <SoftwareSerial.h>
#include <stdlib.h>
#include <SimpleDHT.h>

int pinDHT11 = 4;
SimpleDHT11 dht11;

SoftwareSerial esp8266(2,3); // 2 TX-TX, 3 RX-RX, CH_PD-VCC

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp8266.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:

  byte temperature;
  byte humidity;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(500);
  }
  else{
    Serial.print("Temperature - ");
    Serial.print(temperature); 
    Serial.print("*C || "); 
    Serial.print("Humidity - ");
    Serial.print(humidity); 
    Serial.println("%");

    // Sending data to ESP
    esp8266.print(temperature);
    esp8266.print(humidity);
    Serial.print("Data Transmitted....");

      
    // DHT11 sampling rate is 1HZ (200ms)
    delay(10000);
  }
}
