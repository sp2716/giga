#include <Wire.h>
#include <Ethernet.h>
#include <ArduinoGraphics.h>
#include <Arduino_H7_Video.h>
#include <H7DisplayShield.h>
#include <anx7625.h>
#include <coreboot_tables.h>
#include <dsi.h>
#include <edid.h>
#include <helpers.h>
#include <lv_conf.h>
#include <lv_conf_8.h>
#include <lv_conf_9.h>
#include <st7701.h>
#include <video_modes.h>
#include "version.h"

//Globals are Serial, Serial1, Serial2, Serial3 for the 4 UARTS in the MEGA R1

Arduino_H7_Video Display(800, 480, GigaDisplayShield);

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  while (!Serial) {
    ;  //wait for UART Success
  }
  Serial.println("Starting Setup");
  char buf[100];
  sprintf(buf, "Setup of Main Application Version %.2i.%.2i.%.2i", APP_SW_PART, APP_REV_MAJOR,APP_REV_MINOR);
  Serial.println(buf);
  Display.clear();
  Display.beginDraw();
  Display.stroke(255, 255, 255);
  Display.text(buf, 50, 50);
  Display.endDraw();
}
void loop() {
 
  // put your main code here, to run repeatedly:
   Serial.println("Starting Main Loop");
   while(1){
    //trap
    ;
   }
}
