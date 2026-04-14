#include <Arduino.h>
#include <ESPmDNS.h>
#include <U8g2lib.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>

#include "sntp.h"
#include "time.h"

#define SDA 4
#define SCL 5
#define SSD_RESET 2

const char* ssid = "........";
const char* password = "........";

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char* time_zone = "GMT0BST,M3.5.0/1,M10.5.0";  // POSIX string for Europe/London

U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
WebServer server(80);

// Functions
void timeavailable(struct timeval* t);
void printLocalTime();

void setup() {
  u8g2.begin();

  // Time
  sntp_set_time_sync_notification_cb(timeavailable);
  sntp_servermode_dhcp(1);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("capacitor-alarm-clock")) {
    Serial.println("MDNS responder started");
  }
}

void loop() {
  u8g2.firstPage();

  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0, 20, "Hello World!");
  } while (u8g2.nextPage());
}

// Callback function (gets called when time adjusts via NTP)
void timeavailable(struct timeval* t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}