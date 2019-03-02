#include "statecontroller.h"

#include <Arduino.h>

typedef unsigned long ms_time_t; ///< Millisecond time type

StateController::StateController(int buttonPin, StatusAbstract *statusLed, OutputAbstract *lights) :
    _buttonPin(buttonPin),
    _statusLed(statusLed),
    _lights(lights)
{
    // Set up button
    pinMode(_buttonPin, INPUT);
    digitalWrite(_buttonPin, HIGH);

    // Initialize in idle state
    setState(States::State::Idle);
}

States::State StateController::getState()
{
    return _currentState;
}

void StateController::processEvents()
{
    // Check button status
    if (buttonHeld()) {
        if (!_buttonActive) {
            // Mark button as being held down
            _buttonStartHold = millis();
            _buttonActive = true;
            _buttonReleased = false;
        }

        if (buttonHeldDuration() >= MS_BUTTON_HELD_LONG && _buttonEventTriggered == false) {
            // Button has been held longer than LONG duration, fire event
            buttonTriggered();
            _buttonEventTriggered = true;
        }
    } else {
        // Button not held, or held longer than maximum duration
        if (_buttonActive && !_buttonReleased) {
            // Fire button if not already triggered
            if (_buttonEventTriggered) {
                // Button already triggered, just reset event
                _buttonEventTriggered = false;
            } else {
                // Trigger button
                buttonTriggered();
            }
            _buttonReleased = true;
        }
        _buttonActive = false;
    }
}

void StateController::markLinked()
{
    if (getState() != States::State::Linked) {
        setState(States::State::Linked);
    }
}

bool StateController::buttonHeld()
{
    // Check if button is active/pressed
    return (digitalRead(_buttonPin) == LOW);
}

ms_time_t StateController::buttonHeldDuration()
{
    if (!_buttonActive) {
        return 0;
    }
    // Calculate how long button has been held
    ms_time_t duration = millis() - _buttonStartHold;
    // Clip to 0, no negative values
    return (duration > 0 ? duration : 0);
}

void StateController::buttonTriggered()
{
    if (buttonHeldDuration() >= MS_BUTTON_HELD_LONG) {
        // Turn off lights if held
        setState(States::State::DisplayBlack);
    } else if (buttonHeldDuration() >= MS_BUTTON_HELD_SHORT) {
        // Increment to next state
        switch (getState()) {
        case States::State::Idle:
        case States::State::Linked:
        case States::State::DisplayBlack:
            // Treat idle, linked to computer, and black as the same state
            setState(States::State::DisplayIdentify);
            break;
        case States::State::DisplayIdentify:
            setState(States::State::DisplayDarkOrange);
            break;
        case States::State::DisplayDarkOrange:
            setState(States::State::DisplayOrange);
            break;
        case States::State::DisplayOrange:
            setState(States::State::DisplayAmbient);
            break;
        case States::State::DisplayAmbient:
            setState(States::State::DisplayWhite);
            break;
        case States::State::DisplayWhite:
            setState(States::State::DisplayIdentify);
            break;
        }
    }
}

void StateController::setState(States::State newState)
{
    if (newState == getState() && _setOnce == true) {
        // State already set and startup (setOnce) passed
        return;
    }

    // Track number of LEDs for later
    int numLEDs = _lights->getNumLEDs();

    // Apply new state
    switch (newState) {
    case States::State::Idle:
    case States::State::Linked:
        // Do nothing
        break;
    case States::State::DisplayBlack:
        // Turn lights off
        _statusLed->setBusy(true);
        _lights->fillColor(sCRGB::Black, 255);
        _lights->show();
        _statusLed->setBusy(false);
        break;
    case States::State::DisplayIdentify:
        // Display ends and middle on black
        _statusLed->setBusy(true);
        // Fill with black
        _lights->fillColor(sCRGB::Black, 255);
        // Start LEDs
        _lights->setColor(0, _lights->getCorrectedColor(sCRGB::Red));
        _lights->setColor(1, _lights->getCorrectedColor(sCRGB::Yellow));
        // Middle LEDs
        _lights->setColor((numLEDs / 2) - 2, _lights->getCorrectedColor(sCRGB::Yellow));
        _lights->setColor((numLEDs / 2) - 1, _lights->getCorrectedColor(sCRGB::Purple));
        _lights->setColor((numLEDs / 2) + 0, _lights->getCorrectedColor(sCRGB::Blue));
        _lights->setColor((numLEDs / 2) + 1, _lights->getCorrectedColor(sCRGB::Yellow));
        // Ending LEDs
        _lights->setColor(numLEDs - 2, _lights->getCorrectedColor(sCRGB::Yellow));
        _lights->setColor(numLEDs - 1, _lights->getCorrectedColor(sCRGB::Green));
        _lights->show();
        _statusLed->setBusy(false);
        break;
    case States::State::DisplayDarkOrange:
        // Fill with a dark orange color
        _statusLed->setBusy(true);
        _lights->fillColor(_lights->getCorrectedColor(sCRGB::OrangeRed), 30);
        _lights->show();
        _statusLed->setBusy(false);
        break;
    case States::State::DisplayOrange:
        // Fill with a bright orange color
        _statusLed->setBusy(true);
        _lights->fillColor(_lights->getCorrectedColor(sCRGB::OrangeRed), 255);
        _lights->show();
        _statusLed->setBusy(false);
        break;
    case States::State::DisplayAmbient:
        // Fill with a color loosely approximating normal lighting
        _statusLed->setBusy(true);
        _lights->fillColor(sCRGB(255, 130, 20), 255);
        _lights->show();
        _statusLed->setBusy(false);
        break;
    case States::State::DisplayWhite:
        // Fill with maximum color
        _statusLed->setBusy(true);
        _lights->fillColor(sCRGB::White, 255);
        _lights->show();
        _statusLed->setBusy(false);
        break;
    }

    // Update the status LED
    _statusLed->setState(newState);

    // Store the new state
    _currentState = newState;
    _setOnce = true;
}
