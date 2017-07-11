// When connecting to ESP to Arduino for Serial Connection
// Connect TX-TX and RX-RX
// CH_PD -> 3.3V
// VCC -> 3.3V
// GnD -> Common GND
// Arduino RESET -> GND
// When Programming GPIO0 -> GnD
// When using LED GPIO2 -> LED 
// Programmer Arduino as ISP

void setup(){
  pinMode(2,OUTPUT);
  }

void loop(){
  digitalWrite(2,HIGH);
  delay(200);
  digitalWrite(2,LOW);
  delay(500);
  }
