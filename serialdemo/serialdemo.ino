#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(5000);
  //while(!Serial){}
  Serial.println("Starting Application");
}
void loop() {
  static int n;
  // put your main code here, to run repeatedly:
  Serial.print("Loop executed ");
  Serial.print(n++);
  Serial.println("times");
  delay(1000);
}