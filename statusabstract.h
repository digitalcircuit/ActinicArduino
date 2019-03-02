#ifndef __INC_AA_STATUS_ABSTRACT
#define __INC_AA_STATUS_ABSTRACT

#include <stdint.h>

#include "states.h"

/**
 * Abstract status indicator
 */
class StatusAbstract
{
public:
    /**
     * Constructs a new abstract status indicator
     */
    StatusAbstract() = default;

    /**
     * Sets whether the status should show as busy
     *
     * @param busy  If true, show as busy, otherwise show the current state
     */
    virtual void setBusy(bool busy) = 0;

    /**
     * Sets the indicator to the current system state
     *
     * @param state  Current system state
     */
    virtual void setState(States::State state) = 0;
};

#endif
