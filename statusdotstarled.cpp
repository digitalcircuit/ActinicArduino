#include "statusdotstarled.h"

#include <Arduino.h>

StatusDotStarLed::StatusDotStarLed(int dataPin, int clockPin, uint8_t rgbOrder) :
    _led(NUM_PIXELS, rgbOrder, dataPin, clockPin)
{
    // Initialize DotStar output and set to a known state
    _led.initialize();
    setLedColor(sCRGB::Black);
}

void StatusDotStarLed::setBusy(bool busy)
{
    if (busy) {
        // Mark busyness with yellow
        setLedColor(sCRGB::Yellow, 64);
    } else {
        // Return to previous state
        setState(_lastState);
    }
}

void StatusDotStarLed::setState(States::State state)
{
    switch (state) {
    case States::State::Idle:
        // Set to white when device first starts, to make it easy to see
        setLedColor(sCRGB::White, 90);
        break;
    case States::State::Linked:
        // Set to green when connected, all's good
        setLedColor(sCRGB::Green, 90);
        break;
    case States::State::DisplayBlack:
        // Set to red when turning off
        setLedColor(sCRGB::Red, 64);
        break;
    case States::State::DisplayIdentify:
    case States::State::DisplayDarkOrange:
    case States::State::DisplayOrange:
    case States::State::DisplayAmbient:
    case States::State::DisplayWhite:
        // Set to blue when setting to a non-linked visual state
        setLedColor(sCRGB::Blue, 90);
        break;
    }
    // Track current state
    _lastState = state;
}

void StatusDotStarLed::setLedColor(sCRGB color)
{
    // Set the first (and only) pixel to color at maximum brightness
    _led.setColor(0, color);
    // Display immediately
    _led.show();
}

void StatusDotStarLed::setLedColor(sCRGB color, uint8_t brightness)
{
    // Set the first (and only) pixel to color and brightness
    _led.setColor(0, color, brightness);
    // Display immediately
    _led.show();
}
