#ifndef __INC_AA_STATE_CONTROLLER
#define __INC_AA_STATE_CONTROLLER

#include <stdint.h>

#include "states.h"
#include "outputabstract.h"
#include "statusabstract.h"

/**
 * State machine and event manager
 */
class StateController
{
public:
    /**
     * Constructs a state controller with the given peripherals
     *
     * @param buttonPin  Pin connected to a push button, for manual control
     * @param statusLed  Configured status LED peripheral
     * @param lights     Configured light strand
     */
    StateController(int buttonPin, StatusAbstract *statusLed,
        OutputAbstract *lights);

    /**
     * Get the current system state
     */
    States::State getState();

    /**
     * Process events and check for button input (call in main loop)
     */
    void processEvents();

    /**
     * Mark the system as receiving commands from the linked computer
     */
    void markLinked();

private:
    typedef unsigned long ms_time_t;           ///< Millisecond time type
    const ms_time_t MS_BUTTON_HELD_SHORT = 50; ///< Short button press in ms
    const ms_time_t MS_BUTTON_HELD_LONG = 500; ///< Long button press in ms

    /**
     * Gets whether or not the button is pressed
     *
     * @return True if held, otherwise false
     */
    bool buttonHeld();

    /**
     * Gets how long the button has been held
     *
     * @return How long the button has been held in ms, or 0 if not held
     */
    ms_time_t buttonHeldDuration();

    /**
     * Performs the actions for when the button is pressed and released
     */
    void buttonTriggered();

    /**
     * Set the system state, applying actions as needed
     *
     * @param newState  The new system state
     */
    void setState(States::State newState);

    ms_time_t _buttonStartHold = {};    ///< Tracks start time of the button press
    bool _buttonActive = false;         ///< If button is held
    bool _buttonEventTriggered = false; ///< If button event has been run
    bool _buttonReleased = true;        ///< If button has been released

    States::State _currentState = {}; ///< Current system state
    bool _setOnce = false;            ///< If state has been set at least once

    int _buttonPin = {};                  ///< Pin button is connected to
    StatusAbstract *_statusLed = nullptr; ///< Configured status LED
    OutputAbstract *_lights = nullptr;    ///< Configured light strand
};

#endif
