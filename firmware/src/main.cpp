#include <Arduino.h>
#include <Preferences.h>
#include <WiFiClient.h>
#include <Wire.h>

#include "display.hpp"
#include "secrets.h"
#include "sntp.h"
#include "time.h"

#ifndef BUILD_TEST_ESP8266
// Building for final PCB
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>
#else
// Building for test ESP8266
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";

// POSIX string for Europe/London
// full list at https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h for other timezones :)
const char* time_zone = "GMT0BST,M3.5.0/1,M10.5.0";

#ifndef BUILD_TEST_ESP8266
WebServer server(80);
#else
ESP8266WebServer server(80);
#endif

Preferences prefs;

// Functions
void timeavailable(struct timeval* t);
void printLocalTime();

void setup() {
    Serial.begin(115200);

    display_init();

//     // Time
// #ifndef BUILD_TEST_ESP8266
//     sntp_set_time_sync_notification_cb(timeavailable);
// #endif
//     sntp_servermode_dhcp(1);
//     configTzTime(time_zone, ntpServer1, ntpServer2);

//     WiFi.mode(WIFI_STA);
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//     // Wait for connection
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("");
//     Serial.print("Connected to ");
//     Serial.println(WIFI_SSID);
//     Serial.print("IP address: ");
//     Serial.println(WiFi.localIP());

//     if (MDNS.begin("capacitor-alarm-clock")) {
//         Serial.println("MDNS responder started");
//     }
}

void loop() {
    display_loop();

    delay(500);
}

// // Callback function (gets called when time adjusts via NTP)
// void timeavailable(struct timeval* t) {
//     Serial.println("Got time adjustment from NTP!");
//     printLocalTime();
// }

// void printLocalTime() {
//     struct tm timeinfo;
//     if (!getLocalTime(&timeinfo)) {
//         Serial.println("No time available (yet)");
//         return;
//     }
//     Serial.print(timeinfo.tm_hour);
//     Serial.print(":");
//     Serial.print(timeinfo.tm_min);
//     Serial.print(":");
//     Serial.println(timeinfo.tm_sec);
// }