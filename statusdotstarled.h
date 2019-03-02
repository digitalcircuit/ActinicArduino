#ifndef __INC_AA_STATUS_DOTSTAR_LED
#define __INC_AA_STATUS_DOTSTAR_LED

#include <stdint.h>

//#include <Adafruit_DotStar.h>

#include "color.h"
#include "outputadafruitdotstar.h"
#include "states.h"
#include "statusabstract.h"

/**
 * Adafruit DotStar pixel status indicator
 *
 * NOTE: This is a third-party project, unaffiliated with Adafruit.
 *
 * See https://learn.adafruit.com/adafruit-dotstar-leds
 */
class StatusDotStarLed : public StatusAbstract
{
public:
    /**
     * Constructs a new Adafruit DotStar pixel status indicator
     *
     * @param dataPin   Data pin of the DotStar pixel
     * @param clockPin  Clock pin of the DotStar pixel
     * @param rgbOrder  RGB ordering of pixel, e.g. DOTSTAR_BGR
     */
    StatusDotStarLed(int dataPin, int clockPin, uint8_t rgbOrder);

    virtual void setBusy(bool busy) override;
    virtual void setState(States::State state) override;

private:
    const int NUM_PIXELS = 1; ///< Number of pixels - only 1 is supported

    /**
     * Sets the status LED to the given color at maximum brightness
     *
     * @param color  Color as sCRGB
     */
    void setLedColor(sCRGB color);

    /**
     * Sets the status LED to the given color and brightness
     *
     * @param color       Color as sCRGB
     * @param brightness  Brightness in range 0-255, 255 being maximum
     */
    void setLedColor(sCRGB color, uint8_t brightness);

    OutputAdafruitDotStar _led;    ///< Internal DotStar LED output
    States::State _lastState = {}; ///< Last set system state
};

#endif
