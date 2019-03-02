#include "protocol.h"

#include <Arduino.h>

#include "device_config.h"

namespace Protocol
{
    void print_header() {
        // Firmware version and hardware information, used by Actinic to automatically detect controllers
        // Use F() to use PROGMEM instead of wasting SRAM

        // Protocol identifier
        Serial.println(F("ActinicArduino"));

        // Version
        Serial.print(F("version:"));
        Serial.print(Protocol::VERSION_MAJOR);
        Serial.print(F("."));
        Serial.println (Protocol::VERSION_MINOR);

        // Light count
        Serial.print(F("light_count:"));
        Serial.println (LIGHT_COUNT);

        // Strand length
        Serial.print(F("strand_length:"));
        Serial.println (STRAND_LENGTH);

        // Maximum color value
        Serial.print(F("color_max:"));
        Serial.println (MAX_COLOR);

        // Maximum brightness value
        Serial.print(F("bright_max:"));
        Serial.println (MAX_BRIGHTNESS);

        // End
        Serial.println(F("end_init"));
    }
}
