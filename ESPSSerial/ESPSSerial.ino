// This code can be used with ESP8266 to 
// 1. Send AT Commands
// 2. If ESP contains the ESPSerialCom code then it will echo
//    back the data sent to the ESP via RX_TX lines
//
// Synchronize the Baudrate
// SoftwareSerial doesnot works best with 9600 baud
//
// Connections
// TX-TX
// RX-RX
// VCC-3.3v
// GND-GND
// CH_PD-3.3v

#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2,3); // 2 TX, 3 RX
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); 
}
 
void loop()
{
  while(esp8266.available())
  {
    String c = "";
    c += (char)esp8266.read();
    Serial.print(c);  
  }

  while(Serial.available())
  { 
    String command="";
    command+= (char)Serial.read();
    esp8266.print(command);
  }
}
