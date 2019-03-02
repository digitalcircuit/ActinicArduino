#ifndef __INC_AA_DEVICE_CONFIG
#define __INC_AA_DEVICE_CONFIG

// Edit these to set your device parameters, then remove the
// "Example configurations" down below.

/*  // <- Don't forget to uncomment first

// Configuration template
// --------

// Total # of lights on string
#define LIGHT_COUNT (150)

// Lighted length of the string
#define STRAND_LENGTH (13.0)

// Button input
#define BUTTON_PIN (2)

// Pick an LED output
// --------
// Adafruit DotStar
//#include "outputadafruitdotstar.h"
//extern OutputAdafruitDotStar lights;
//#define DEC_OUTPUT OutputAdafruitDotStar lights(LIGHT_COUNT, DOTSTAR_BGR);

// FastLED DotStar
//#include "outputfastled.h"
//extern OutputFastLED<DOTSTAR, BGR> lights;
//#define DEC_OUTPUT OutputFastLED<DOTSTAR, BGR> lights(LIGHT_COUNT);

// GE G35
//#include "outputg35.h"
//#define G35_PIN (11)
//extern OutputG35 lights;
//#define DEC_OUTPUT OutputG35 lights(LIGHT_COUNT, G35_PIN);
//
// Note: Length is usually 50, 48, or 36. Maximum is 63, because the protocol
// uses 6-bit addressing and bulb #63 is reserved for broadcast messages.

// Pick a status LED output
// --------
// On/off status indicator LED
//#include "statussimpleled.h"
//#define STATUS_LED_PIN (LED_BUILTIN)
//extern StatusSimpleLed statusLed;
//#define DEC_STATUS StatusSimpleLed statusLed(STATUS_LED_PIN);

// DotStar status indicator LED
//#include "statusdotstarled.h"
//#define STATUS_DOTSTAR_DATAPIN   (8)
//#define STATUS_DOTSTAR_CLOCKPIN  (6)
//extern StatusDotStarLed statusLed;
//#define DEC_STATUS StatusDotStarLed statusLed(STATUS_DOTSTAR_DATAPIN, STATUS_DOTSTAR_CLOCKPIN);

*/


// Example configurations
// (Comment these out or remove this when setting your own)
// /*
// --------
#if defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    // ItsyBitsy with 10m of 30 LED/m DotStar LEDs
    // --------
    #define LIGHT_COUNT   (300)
    #define STRAND_LENGTH (10.0)

    #define BUTTON_PIN (2)

    // Adafruit DotStar
    #include "outputadafruitdotstar.h"
    extern OutputAdafruitDotStar lights;
    #define DEC_OUTPUT OutputAdafruitDotStar lights(LIGHT_COUNT, DOTSTAR_BGR);

    // DotStar status indicator LED
    #include "statusdotstarled.h"
    #define STATUS_DOTSTAR_DATAPIN   (8)
    #define STATUS_DOTSTAR_CLOCKPIN  (6)
    extern StatusDotStarLed statusLed;
    #define DEC_STATUS StatusDotStarLed statusLed(STATUS_DOTSTAR_DATAPIN, STATUS_DOTSTAR_CLOCKPIN, DOTSTAR_BGR);

#elif defined(ARDUINO_AVR_UNO)
    // Arduino Uno with 13m of GE ColorEffects G-35 LEDs
    // --------
    #define LIGHT_COUNT   (50)
    #define STRAND_LENGTH (13.0)

    #define BUTTON_PIN (2)

    // GE G35
    #include "outputg35.h"
    #define G35_PIN (11)
    extern OutputG35 lights;
    #define DEC_OUTPUT OutputG35 lights(LIGHT_COUNT, G35_PIN);

    // On/off status indicator LED
    #include "statussimpleled.h"
    #define STATUS_LED_PIN (LED_BUILTIN)
    extern StatusSimpleLed statusLed;
    #define DEC_STATUS StatusSimpleLed statusLed(STATUS_LED_PIN);

#endif

// */

#endif
