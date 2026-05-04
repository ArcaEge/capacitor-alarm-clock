#include "display.hpp"
#include "includes.hpp"
#include "config.h"
#include "server.hpp"
#include "state.hpp"
#include "alarm.hpp"
#include "inputs.hpp"

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";

const char* time_zone = TZ;

void setup() {
    Serial.begin(115200);

    inputs_init();
    alarm_init();
    display_init(state);

    // Load state
    state.prefs.begin("capacitor-alarm-clock");

    Serial.println("Loading schedule");
    if (state.prefs.getBytes("persistent", &state.persistent, sizeof(state.persistent))) {
        Serial.println("Schedule loaded");
    } else {
        Serial.println("No schedule exists, loaded empty schedule");
    }

    sntp_servermode_dhcp(1);
    configTzTime(time_zone, ntpServer1, ntpServer2);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
    state.wifi.connected = WiFi.status() == WL_CONNECTED;

    inputs_loop(state);

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

            server_init(state);
        }

        state.wifi.previouslyConnected = true;

        server_handle();
    }

    if (state.wifi.previouslyConnected)
        state.time.available = getLocalTime(&state.time.info);

    alarm_loop(state);
    display_loop(state);

    delay(2);
}
