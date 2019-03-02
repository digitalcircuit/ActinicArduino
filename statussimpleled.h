#ifndef __INC_AA_STATUS_SIMPLE_LED
#define __INC_AA_STATUS_SIMPLE_LED

#include <stdint.h>

#include "states.h"
#include "statusabstract.h"

/**
 * Simple LED status indicator
 */
class StatusSimpleLed : public StatusAbstract
{
public:
    /**
     * Constructs a new simple LED status indicator at the given pin
     *
     * @param ledPin  Pin connected to LED
     */
    StatusSimpleLed(int ledPin);

    virtual void setBusy(bool busy) override;
    virtual void setState(States::State state) override;

private:
    /**
     * Sets whether or not the LED is on
     *
     * @param ledOn  If true, set LED on, otherwise set LED off
     */
    void setLedOn(bool ledOn);

    int _ledPin;                   ///< Pin LED is connected to
    States::State _lastState = {}; ///< Last set system state
};

#endif
