#include "Arduino_GigaDisplay_GFX.h"
#include "Fonts/FreeSans12pt7b.h"
#include <WiFi.h>
#include <SDRAM.h>
#include "version.h"
#include "ourtypes.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h

char ssid[] = "TPL184";    // your network SSID (name)
char pass[] = "02477480";  // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
WiFiClient client;


//Giga Display Shield Example
GigaDisplay_GFX tft;

void ConfigureDisplay() {
  tft.begin();
  tft.setRotation(1);
  tft.setTextWrap(1);
  tft.setFont(&FreeSans12pt7b);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  
}

bool ConfigureWifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    tft.println("Communication with WiFi module failed");
    return false;
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    tft.print("Connecting To SSID: ");
    tft.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open network:
    status = WiFi.begin(ssid, pass);
  }
  printWifiStatus();
  return true;
}

void printWifiStatus() {
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.print("SSID: ");
  tft.println(WiFi.SSID());
  tft.print("MAC Address: ");
  tft.println(WiFi.macAddress());
  tft.print("Local Address: ");
  tft.println(WiFi.localIP());
  tft.print("Rx Signal Strength:");
  tft.print(WiFi.RSSI());
  tft.println(" dBm");
}

void setup() {
  ConfigureDisplay();
  ConfigureWifi();
}

void loop(void) {
  
}
