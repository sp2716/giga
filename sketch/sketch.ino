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
#include <lvgl.h>


#define BLACK 0x0000

//Globals are Serial, Serial1, Serial2, Serial3 for the 4 UARTS in the MEGA R1

//Initialize Giga Display Shield with global application interface
Arduino_H7_Video Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch TouchDetector;

//buffer for serial output messages
char buf[100];


void* worker(void* vargs) {
  return NULL;
}

void setup() {

  delay(3000);
  // put your setup code here, to run once:
  //Initialize UART0
  Serial.begin(115200);
  while (!Serial) { ; }
  Serial.println("UART0 Initialized at 115200 baud");
  //intialize I2C interface for sensors
  //Wire.begin();

  sprintf(buf, "Software P\N %s Revision %.2i.%.2i.%.2i",
          APP_SW_PART, APP_REV_METRO, APP_REV_MAJOR, APP_REV_MINOR);
  Serial.println(buf);
  //initialize display interface

  delay(3000);
  Display.begin();
  TouchDetector.begin();

  //Display & Grid Setup
  lv_obj_t* screen = lv_obj_create(lv_scr_act());
  lv_obj_set_size(screen, Display.width(), Display.height());

  static lv_coord_t col_dsc[] = { 370, 370, LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { 215, 215, 215, 215, LV_GRID_TEMPLATE_LAST };

  lv_obj_t* grid = lv_obj_create(lv_scr_act());
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
  lv_obj_set_size(grid, Display.width(), Display.height());

  //top left
  lv_obj_t* obj;
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 0, 1);      //row

  //bottom left
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 1, 1);      //row
  //top right
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 0, 1);      //row

  //bottom right
  obj = lv_obj_create(grid);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1,  //column
                       LV_GRID_ALIGN_STRETCH, 1, 1);      //row
}

void loop() {
  
  uint32_t msDelay = lv_timer_handler();
  delay(msDelay);
}
