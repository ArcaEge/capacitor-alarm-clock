# firmware

Before compilation, copy `src/config.h.example` to `config.h` and add your WiFi credentials, along with your timezone string. You can then upload to the board.

I didn't have an ESP32 whilst working on the firmware as the parts hadn't arrived yet, so you can also compile this to run on an ESP8266. Choose `nodemcuv2` as the build target to do this. The pinout is in `inputs.hpp`, `alarm.cpp` and `display.hpp`.
