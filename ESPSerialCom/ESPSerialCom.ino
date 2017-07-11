// Code to be uplaoded in ESP8266
// Pins Configuration
// TX-TX
// RX-RX
// GPIO0-GND (while programming)
// VCC,CH_PD-3.3v

// If code shows any error than detach USB and attach again
// Everytime before uploading the code detach and re-attach the USB cable to PC
//
// This program will make ESP -ECHO what has been send to it via Serial Communication
// Use Arduino Serial Monitor to Send and Receive data over TX/RX lines


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String command = "";
  
  while(Serial.available()){
    command += (char)Serial.read();
    if(command.substring(0,command.length())=="a"){
      Serial.print("Found!!"); 
    }
    else{
      Serial.print(command);     
    }
  }

}
