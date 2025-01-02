#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Arduino_GigaDisplay.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay_GFX.h>
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

#define BLACK 0x0000

//Globals are Serial, Serial1, Serial2, Serial3 for the 4 UARTS in the MEGA R1

//Initialize Giga Display Shield with global application interface
GigaDisplay_GFX* pDisplay;

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
  //initialize display interface
  GigaDisplay_GFX Display;
  Display.begin();
  Display.setCursor(10, 10);
  Display.setTextSize(5);
  Display.print(buf);
  //global interface for multi-threading
  pDisplay = &Display;

  Serial.println("Initialization Complete - Starting Application");
}

void loop() {
  pDisplay->fillScreen(BLACK);
  sprintf(buf, "App loop starting at memory address %p", (void*)loop);
  pDisplay->
  Serial.println(buf);
  // put your main code here, to run repeatedly:
  while (1) {
    delayMicroseconds(100 * 1000);  //100ms delay
  }
}
