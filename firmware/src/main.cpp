#include "display.hpp"
#include "includes.hpp"
#include "secrets.h"
#include "state.hpp"

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";

// POSIX string for Europe/London
// full list at https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h for other timezones :)
const char* time_zone = "GMT0BST,M3.5.0/1,M10.5.0";

#ifndef BUILD_TEST_ESP8266
// Building for PCB
#define BTN_L 10
#define BTN_R 9

#define RELAY_1 14
#define RELAY_2 12
#define RELAY_3 13

WebServer server(80);

#else
// Building for test ESP8266
#define BTN_L 10
#define BTN_R 9

#define RELAY_1 14
#define RELAY_2 12
#define RELAY_3 13

ESP8266WebServer server(80);
#endif

Preferences prefs;
State state;

void setup() {
    Serial.begin(115200);

    pinMode(BTN_L, INPUT);
    pinMode(BTN_R, INPUT);

    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    pinMode(RELAY_3, OUTPUT);

    display_init();

    // Time
#ifndef BUILD_TEST_ESP8266
    sntp_set_time_sync_notification_cb(timeavailable);
#endif

    sntp_servermode_dhcp(1);
    configTzTime(time_zone, ntpServer1, ntpServer2);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
    state.wifi.connected = WiFi.status() == WL_CONNECTED;

    if (state.wifi.connected) {
        state.wifi.ip = WiFi.localIP();

        if (!state.wifi.previouslyConnected) {
            Serial.println("");
            Serial.print("Connected to ");
            Serial.println(WIFI_SSID);
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());

            if (MDNS.begin("capacitor-alarm-clock")) {
                Serial.println("MDNS responder started");
            }
        }

        state.wifi.previouslyConnected = true;
    }

    if (state.wifi.previouslyConnected)
        state.time.available = getLocalTime(&state.time.info);

    display_loop(state);

    delay(100);
}
