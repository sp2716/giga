
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
#include <vector>
#include "version.h"

//Globals are Serial, Serial1, Serial2, Serial3 for the 4 UARTS in the MEGA R1

//Initialize Giga Display Shield with global application interface
Arduino_H7_Video Display(800, 480, GigaDisplayShield);

//buffer for serial output messages
char buf[100];

void setup() {
  // put your setup code here, to run once:
  //Initialize UART0
  Serial.begin(115200);
  while (!Serial) { ; }
  Serial.println("UART0 Initialized at 115200 baud");
  //intialize I2C interface for sensors
  //Wire.begin();

  sprintf(buf, "Software P\N %.2i Revision %.2i.%.2i",
          APP_SW_PART, APP_REV_MAJOR, APP_REV_MINOR);
  Serial.println(buf);
  //iniatizlie display output
  Display.clear();
  Display.beginDraw();
  Display.stroke(255, 255, 255);
  Display.text(buf, 50, 50);
  Display.endDraw();

  Serial.println("Initialization Complete - Starting Application");
}

void loop() {
  sprintf(buf, "App loop starting at memory address %p", (void*)loop);
  Serial.println(buf);
  // put your main code here, to run repeatedly:
  while (1) {
    delayMicroseconds(100 * 1000);  //100ms delay
  }
}
