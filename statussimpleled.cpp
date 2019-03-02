#include "statussimpleled.h"

#include <Arduino.h>

StatusSimpleLed::StatusSimpleLed(int ledPin) : _ledPin(ledPin)
{
    // Configure LED output pin and set to a known state
    pinMode(_ledPin, OUTPUT);
    setLedOn(false);
}

void StatusSimpleLed::setBusy(bool busy)
{
    if (busy) {
        // Mark busyness by keeping LED on
        setLedOn(true);
    } else {
        // Return to previous state
        setState(_lastState);
    }
}

void StatusSimpleLed::setState(States::State state)
{
    switch (state) {
    case States::State::Idle:
        // Keep LED on when device first starts, to show readiness
        setLedOn(true);
        break;
    case States::State::Linked:
    case States::State::DisplayBlack:
    case States::State::DisplayIdentify:
    case States::State::DisplayDarkOrange:
    case States::State::DisplayOrange:
    case States::State::DisplayAmbient:
    case States::State::DisplayWhite:
        // Turn LED off in any state, to distinguish from busyness
        setLedOn(false);
        break;
    }
    // Track current state
    _lastState = state;
}

void StatusSimpleLed::setLedOn(bool ledOn)
{
    if (ledOn) {
        // Turn LED on
        digitalWrite(_ledPin, HIGH);
    } else {
        // Turn LED off
        digitalWrite(_ledPin, LOW);
    }
}
