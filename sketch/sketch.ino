#include <Arduino.h>
void setup() {

  Serial.begin(9600);
  //while(!Serial){}
  Serial.println("Hello Sean");
}

void loop() {
  Serial.println("Working");
  
}
