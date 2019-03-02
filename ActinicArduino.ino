/**
 * ActinicArduino: generic LED controller program, designed for use with the
 * companion C# program Actinic.
 *
 * @author Shane Synan <digitalcircuit36939@gmail.com>
 */

// --------
// README:
// Set up your own hardware (LED devices, status LED, etc) in the
// "device_config.h" file.  You shouldn't need to modify anything here.

// General
#include "color.h"
#include "outputabstract.h"
#include "protocol.h"
#include "statusabstract.h"
#include "statecontroller.h"

// Output and board configuration
#include "device_config.h"

// Set up global peripherals (controlled by "device_config.h")
DEC_OUTPUT ///< Declaration of output device
DEC_STATUS ///< Declaration of status device

/// System state machine and events processor
StateController controller(BUTTON_PIN, &statusLed, &lights);

bool commandSent = false;       ///< If a command was sent this loop iteration
bool outputInvalidated = false; ///< If output was changed and needs updated

/**
 * Setup the firmware and peripherals
 */
void setup()
{
    // Initialize to the fastest common serial baud rate
    Serial.begin(115200);

    // Initialize lights and fill with black
    lights.initialize();
    lights.fillColor(sCRGB(0, 0, 0));
    lights.show();
}

/**
 * Main loop to process commands, events, and generate output
 */
void loop()
{
    // Check for pending commands
    if (Serial.available() > 0) {
        // First byte is the command
        char command = Serial.read();

        // Set aside storage for LED commands
        const size_t serial_buffer_size_max = 4;
        char serial_buffer[serial_buffer_size_max];

        // Mark command as sent
        commandSent = true;

        if (command == '\n') {
            // Ignore newlines
        } else if (command == Protocol::Command::QUERY_INFO) {
            // Query for info
            Protocol::print_header();
        } else if (command == Protocol::Command::SET_BRIGHTNESS) {
            // Set brightness
            statusLed.setBusy(true);

            // Store incoming data in a 1 byte buffer
            const size_t bright_data_size = 1;
            static_assert(
                bright_data_size <= serial_buffer_size_max,
                "bright_data_size larger than serial_buffer_size_max"
            );

            // Read data in, 1 pixel at a time, and assign it
            for (int i = 0; i < LIGHT_COUNT; ++i) {
                if (Serial.readBytes(serial_buffer, bright_data_size) == 0) {
                    // Timeout, cancel (partial changes kept)
                    Serial.println(PROTOCOL_MSG_TIMEOUT);
                    break;
                }
                // Set pixel brightness
                lights.setBrightness(i, serial_buffer[0]);
            }
            // Mark output as needing refreshed
            outputInvalidated = true;
        } else if (command == Protocol::Command::SET_COLOR
                   || command == Protocol::Command::SET_HUE) {
            // Set color, resetting or keeping brightness (via COLOR or HUE)
            statusLed.setBusy(true);

            // Store incoming data in a 3 byte buffer
            const size_t rgb_data_size = 3;
            static_assert(
                rgb_data_size <= serial_buffer_size_max,
                "rgb_data_size larger than serial_buffer_size_max"
            );

            bool preserveBrightness =
                (command == Protocol::Command::SET_HUE);

            // Read data in, 1 pixel at a time, and assign it
            for (int i = 0; i < LIGHT_COUNT; ++i) {
                if (Serial.readBytes(serial_buffer, rgb_data_size) == 0) {
                    // Timeout, cancel (partial changes kept)
                    Serial.println(PROTOCOL_MSG_TIMEOUT);
                    break;
                }
                if (preserveBrightness) {
                    // Set pixel color, preserving existing brightness
                    lights.setHue(i,
                        sCRGB(serial_buffer[2], serial_buffer[1], serial_buffer[0]));
                } else {
                    // Set pixel color, resetting brightness
                    lights.setColor(i,
                        sCRGB(serial_buffer[2], serial_buffer[1], serial_buffer[0]));
                }
            }
            // Mark output as needing refreshed
            outputInvalidated = true;
        } else if (command == Protocol::Command::SET_ALL) {
            // Set brightness and color
            statusLed.setBusy(true);

            // Store incoming data in a 4 byte buffer
            const size_t rgba_data_size = 4;
            static_assert(
                rgba_data_size <= serial_buffer_size_max,
                "rgba_data_size larger than serial_buffer_size_max"
            );

            // Read data in, 1 pixel at a time, and assign it
            for (int i = 0; i < LIGHT_COUNT; ++i) {
                if (Serial.readBytes(serial_buffer, rgba_data_size) == 0) {
                    // Timeout, cancel (partial changes kept)
                    Serial.println(PROTOCOL_MSG_TIMEOUT);
                    break;
                }
                // Set pixel brightness and color
                lights.setColor(i,
                    sCRGB(serial_buffer[2], serial_buffer[1], serial_buffer[0]), serial_buffer[3]);
            }
            // Mark output as needing refreshed
            outputInvalidated = true;
        } else {
            // Unknown command
            Serial.println(PROTOCOL_MSG_UNKNOWN_CMD);
        }
    }

    // Process button events, state, etc
    controller.processEvents();

    if (commandSent == true) {
        // Tell the state controller a command's been received
        controller.markLinked();
        commandSent = false;
    }

    if (outputInvalidated) {
        // Send the updates to the lights
        lights.show();
        // Acknowledge the command (only after lights have updated)
        Serial.println(Protocol::Reply::FINISHED);
        // Clear status
        statusLed.setBusy(false);
        outputInvalidated = false;
    }
}
