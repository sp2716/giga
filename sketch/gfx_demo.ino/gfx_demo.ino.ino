#include "Arduino_GigaDisplay_GFX.h"
#include <WiFi.h>

int status = WL_IDLE_STATUS;
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
//NTP Client example using the onboard wifi to connect
char ssid[] = "TPL184";    // your network SSID (name)
char pass[] = "02477480";  // your network password (use for WPA, or use as key for WEP)

unsigned int localPort = 2390;             // local port to listen for UDP packets
IPAddress timeServer(162, 159, 200, 123);  // pool.ntp.org NTP server
const int NTP_PACKET_SIZE = 48;            // NTP timestamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE];        //buffer to hold incoming and outgoing packets
// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

//Giga Display Shield Example
GigaDisplay_GFX tft;
//Some Colors
#define GC9A01A_RED 0xf800
#define GC9A01A_BLUE 0x001F
#define GC9A01A_GREEN 0x07E0
#define GC9A01A_WHITE 0xFFFF
#define GC9A01A_BLACK 0x0000

void setup() {
  Serial.begin(115200);
  while(!Serial){}
  Serial.print("Starting application");
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(1);
  tft.println("Configuring Giga R1...");

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    tft.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    tft.println("Attempting to connect to SSID: ");
    tft.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open network:
    status = WiFi.begin(ssid, pass);

    // wait 3 seconds for connection:
    delay(3000);
  }

  tft.println("Connected to WiFi");
  printWifiStatus();

  tft.println("\nStarting connection to pool.ntp.org server...");
  Udp.begin(localPort);


}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Local Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

static int i = 0;

void loop(void) {
  Serial.println("Sending NTP packet");
   sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  if (Udp.parsePacket()) {
    tft.println("packet received");
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    tft.print("Seconds since Jan 1 1900 = ");
    tft.println(secsSince1900);

    // now convert NTP time into everyday time:
    tft.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    tft.println(epoch);


    // print the hour, minute and second:
    tft.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    tft.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    tft.print(':');
    if (((epoch % 3600) / 60) < 10) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      tft.print('0');
    }
    tft.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    tft.print(':');
    if ((epoch % 60) < 10) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      tft.print('0');
    }
    tft.println(epoch % 60); // print the second
  }
  Serial.print("Waiting 10 seconds for next poll ");
  Serial.println(i++);
  // wait ten seconds before asking for the time again
  delay(10000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
  //Serial.println("1");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //Serial.println("2");
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  //Serial.println("3");

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  //Serial.println("4");
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  //Serial.println("5");
  Udp.endPacket();
  //Serial.println("6");
}

