#include "server.hpp"

#ifndef BUILD_TEST_ESP8266
// Building for PCB
WebServer server(80);
#else
// Building for test ESP8266
ESP8266WebServer server(80);
#endif

void handleRoot(State& state);
void handleSchedulePOST(State& state);
void handleNotFound();

void server_init(State& state) {
    server.on("/", [&state]() { handleRoot(state); });
    server.on("/schedule", [&state]() { handleSchedulePOST(state); });
    server.onNotFound(handleNotFound);
    server.begin();
}

void server_handle() {
    server.handleClient();
}

void handleRoot(State& state) {
    char time[6];
    sprintf(time, "%02d:%02d", state.schedule.time.hours, state.schedule.time.minutes);

    const String homeHtml =
        "<!DOCTYPE html>\
    <html>\
        <head>\
            <title>Capacitor Alarm Clock</title>\
        </head>\
        <body>\
            <h3>capacitor alarm clock configuration</h3>\
            <hr />\
            <form\
                method=\"POST\"\
                action=\"/schedule\"\
            >\
                <label for=\"input-time\">Time:</label>\
                <br />\
                <input type=\"time\" id=\"input-time\" name=\"time\" required value=\"" + String(time) + "\"/>\
                <br />\
                <br />\
                <label for=\"days-select\">Days of week:</label>\
                <br />\
                <select multiple style=\"height: 150px; width: 120px;\" id=\"days-select\" name=\"days\">\
                  <option value=\"0\"" + (state.schedule.weekSchedule[0] ? "selected" : "") + ">Monday</option>\
                  <option value=\"1\"" + (state.schedule.weekSchedule[1] ? "selected" : "") + ">Tuesday</option>\
                  <option value=\"2\"" + (state.schedule.weekSchedule[2] ? "selected" : "") + ">Wednesday</option>\
                  <option value=\"3\"" + (state.schedule.weekSchedule[3] ? "selected" : "") + ">Thursday</option>\
                  <option value=\"4\"" + (state.schedule.weekSchedule[4] ? "selected" : "") + ">Friday</option>\
                  <option value=\"5\"" + (state.schedule.weekSchedule[5] ? "selected" : "") + ">Saturday</option>\
                  <option value=\"6\"" + (state.schedule.weekSchedule[6] ? "selected" : "") + ">Sunday</option>\
                </select>\
                <br />\
                <br />\
                <input type=\"submit\" value=\"Set schedule\" />\
            </form>\
            <hr />\
        </body>\
    </html>\
    ";

    server.send(200, "text/html", homeHtml);
}

void handleSchedulePOST(State& state) {
    if (server.method() != HTTP_POST) server.send(405, "text/plain", "Method Not Allowed");

    bool daysOfWeek[7] = {};

    for (uint8_t i = 0; i < server.args(); i++) {
        String argName = server.argName(i);
        String arg = server.arg(i);

        if (argName == "time") {
            if (arg.length() != 5) {
                server.send(400, "text/plain", "Bad Request: 'time' argument length is not 5");
                return;
            }

            String hours = arg.substring(0, 2);
            state.schedule.time.hours = hours.toInt();
            String minutes = arg.substring(3, 5);
            state.schedule.time.minutes = minutes.toInt();

        } else if (argName == "days") {
            int dayOfWeek = arg.toInt();

            if (dayOfWeek < 0 || dayOfWeek > 7) {
                server.send(400, "text/plain", "Bad Request: invalid day of week");
                return;
            }

            daysOfWeek[dayOfWeek] = true;
        }
    }

    memcpy(state.schedule.weekSchedule, daysOfWeek, 7);
    state.prefs.putBytes("schedule", &state.schedule, sizeof(state.schedule));

    server.sendHeader("Location", "/");
    server.send(307, "text/plain", "");
}

void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}
