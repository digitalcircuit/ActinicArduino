#ifndef __INC_AA_PROTOCOL
#define __INC_AA_PROTOCOL

#include <stdint.h>

// Standard protocol messages

#define PROTOCOL_MSG_TIMEOUT F("timeout")
#define PROTOCOL_MSG_UNKNOWN_CMD F("Unknown command")
// Note: this results in duplicate PROGMEM strings.  If flash space is low, try
// an alternative solution, such as the following:
// https://forum.arduino.cc/index.php?topic=110307.0
// http://linux.dd.com.au/wiki/Arduino_Static_Strings

/**
 * Standard protocol definitions
 */
namespace Protocol
{
    /**
     * Current Arduino protocol major version.  This must match what Actinic
     * expects for negotiation to succeed.
     */
    constexpr int VERSION_MAJOR = 3;

    /**
     * Current Arduino protocol minor version.  This represents
     * backwards-compatible changes.
     */
    constexpr int VERSION_MINOR = 0;

    /// Maximum value for color
    constexpr uint8_t MAX_COLOR = 255;

    /// Maximum value for brightness
    constexpr uint8_t MAX_BRIGHTNESS = 255;

    /**
     * Print the protocol header over serial
     */
    void print_header();

    /**
     * Available commands
     */
    namespace Command
    {
        /// Display device information
        constexpr char QUERY_INFO = '?';

        /// Set output brightness and color
        constexpr char SET_ALL = 'A';

        /// Set output brightness
        constexpr char SET_BRIGHTNESS = 'B';

        /// Set output color, setting brightness to maximum
        constexpr char SET_COLOR = 'C';

        /// Set output color, preserving existing brightness
        constexpr char SET_HUE = 'H';
    }

    /**
     * Available replies
     */
    namespace Reply
    {
        /// Set command finished
        constexpr char FINISHED = '#';
    }
}
#endif
