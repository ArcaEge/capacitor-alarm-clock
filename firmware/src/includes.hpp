#include <Arduino.h>
#include <Preferences.h>
#include <WiFiClient.h>
#include <Wire.h>

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