#include <Ethernet.h>

#include "Arduino_H7_Video.h"
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include "Arduino_BMI270_BMM150.h"
#include <lvgl.h>
#include <stdio.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x00, 0x40, 0xBE, 0x11, 0xA4, 0x8A
};
IPAddress ip(192, 168, 1, 125);

//Create rgb object
GigaDisplayRGB rgb;

Arduino_H7_Video          Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch  TouchDetector;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

/* Slider red value changed event callback */
static void red_event_cb(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t *)lv_event_get_target(e);
  int32_t value = lv_slider_get_value(slider);
  set_rgb_color(0, (uint8_t)value);
}

/* Slider green value changed event callback */
static void green_event_cb(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t *)lv_event_get_target(e);
  int32_t value = lv_slider_get_value(slider);
  set_rgb_color(1, (uint8_t)value);
}

/* Slider blue value changed event callback */
static void blue_event_cb(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t *)lv_event_get_target(e);
  int32_t value = lv_slider_get_value(slider);
  set_rgb_color(2, (uint8_t)value);
}

/* Convenience method to set the red, green, and blue values of the RGB LED individually while remembering the other values */
void set_rgb_color(int color, uint8_t val) {
  static uint8_t red = 0;
  static uint8_t green = 0;
  static uint8_t blue = 0;

  if (color == 0) {
    red = val;
  } else if (color == 1) {
    green = val;
  } else if (color == 2) {
    blue = val;
  }
  rgb.on(red, green, blue);
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Started Application");
  rgb.begin();
  Display.begin();
  TouchDetector.begin();
  DisplaySetup();
  //Ethernet initialization
  Ethernet.begin(mac,ip);

  switch(Ethernet.hardwareStatus()){
    case EthernetNoHardware:
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
    break;
    case EthernetW5500:
      Serial.println("W5500 Detected (8 concurrent supported sockets)"); break;
    case EthernetW5200:
      Serial.println("W5200 Detected"); break;
      default:
      Serial.println("W5100 Detected"); break;
  }
 
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
void DisplaySetup(){
    /* Create a container with grid 2x2 */
  static lv_coord_t col_dsc[] = {370, 370, LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {215, 215, LV_GRID_TEMPLATE_LAST};
  lv_obj_t * cont = lv_obj_create(lv_scr_act());
  lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
  lv_obj_set_size(cont, Display.width(), Display.height());
  lv_obj_set_style_bg_color(cont, lv_color_hex(0x03989e), LV_PART_MAIN);
  lv_obj_center(cont);

  lv_obj_t * label;
  lv_obj_t * obj;
  uint16_t idx = 0u;
    /* [0;1] - Sliders for RGB LED */
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                        LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);      

  label = lv_label_create(obj);                  
  lv_label_set_text(label, "LED COLOR PICKER");
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align( label, LV_ALIGN_TOP_MID, 0, 0 );
  
  lv_obj_t * slider = lv_slider_create(obj);
  lv_slider_set_range(slider, 0, 255);
  lv_slider_set_value(slider, 75, LV_ANIM_OFF);
  lv_obj_center(slider);
  label = lv_label_create(obj);
  lv_label_set_text(label, "RED");
  lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_obj_add_event_cb(slider, red_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  slider = lv_slider_create(obj);
  lv_slider_set_range(slider, 0, 255);
  lv_slider_set_value(slider, 80, LV_ANIM_OFF);
  lv_obj_center(slider);
  label = lv_label_create(obj);
  lv_label_set_text(label, "GREEN");
  lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20); 
  lv_obj_add_event_cb(slider, green_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  slider = lv_slider_create(obj);
  lv_slider_set_range(slider, 0, 255);
  lv_slider_set_value(slider, 50, LV_ANIM_OFF);
  lv_obj_center(slider);
  label = lv_label_create(obj);
  lv_label_set_text(label, "BLUE");
  lv_obj_align_to(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);   
  lv_obj_add_event_cb(slider, blue_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  rgb.on(75, 80, 50);
}

void loop() {
    /* Feed LVGL engine */
  lv_timer_handler();
  
    // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an HTTP request ends with a blank line
    bool currentLineIsBlank = true;
              char buf[10];
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        static int i;
        if (c == '\n' && currentLineIsBlank) {
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<p>");
          client.println("Here is dynamic content: <br>");
          sprintf(buf,"%i",i);
          client.println(buf);
          client.println("</p>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    
  }
  
}
