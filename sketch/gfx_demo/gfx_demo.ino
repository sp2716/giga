#include "Arduino_GigaDisplay_GFX.h"
#include <WiFi.h>
#include <SDRAM.h>
#include "version.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
//NTP Client example using the onboard wifi to connect
char ssid[] = "TPL184";    // your network SSID (name)
char pass[] = "02477480";  // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// IPAddress server(93,184,216,34);  // IP address for example.com (no DNS)
char server[] = "https://www.timeapi.io/api/timezone/ip?ipAddress=70.90.239.142";  // host name for example.com (using DNS)

WiFiClient client;

//Giga Display Shield Example
GigaDisplay_GFX tft;
//Some Colors
#define GC9A01A_RED 0xf800
#define GC9A01A_BLUE 0x001F
#define GC9A01A_GREEN 0x07E0
#define GC9A01A_WHITE 0xFFFF
#define GC9A01A_BLACK 0x0000

bool ConfigureDisplay() {
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(GC9A01A_GREEN);
  tft.setTextSize(2);
  txt.println(WiFi.macAddress());
  return true;
}

bool ConfigureWifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    tft.println("Communication with WiFi module failed!");
    return false;
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    tft.println("Attempting to connect to SSID: ");
    tft.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open network:
    status = WiFi.begin(ssid, pass);
    // wait 1 seconds for connection:
    delay(1000);
  }

  tft.println("Wifi connection successful");
  printWifiStatus();

  tft.println("\nStarting connection to pool.ntp.org server");
  Udp.begin(localPort);
  return true;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  tft.print("SSID: ");
  tft.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  tft.print("Local Address: ");
  tft.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  tft.print("signal strength (RSSI):");
  tft.print(rssi);
  tft.println(" dBm");
}

void setup() {
  ConfigureDisplay();
  ConfigureWifi();
}

void loop(void) {
}
