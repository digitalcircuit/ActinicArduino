#ifndef __INC_AA_OUTPUT_FASTLED
#define __INC_AA_OUTPUT_FASTLED

#include <stdint.h>

#include <FastLED.h>

#include "color.h"
#include "outputabstract.h"

/**
 * FastLED generic output
 *
 * See http://fastled.io/
 */
template <ESPIChipsets CHIPSET, EOrder RGB_ORDER>
class OutputFastLED : public OutputAbstract
{
public:
    /**
     * Constructs a new FastLED output
     *
     * @param numLEDs  Number of LEDs
     */
    OutputFastLED(int numLEDs) : OutputAbstract(numLEDs)
    {
        // Initialize the arrays and add the LEDs
        _leds = new CRGB[numLEDs];
        FastLED.addLeds<CHIPSET, RGB_ORDER>(_leds, numLEDs);
    }

    /**
     * Destroys the FastLED output
     */
    ~OutputFastLED()
    {
        delete [] _leds;
    }

    virtual bool isSoftwareBrightness() override
    {
        // FastLED only supports global brightness at the hardware level on
        // some chips.  Per-pixel control isn't supported.
        return true;
    }

    virtual void initialize() override
    {
        // Initialize the LED display
    }

    virtual void show() override
    {
        // Update the LED display
        FastLED.show();
    }

    virtual void setBrightness(int index, uint8_t brightness) override
    {
        // Set LED to given brightness
        // TODO: software brightness as per OutputAdafruitDotStar
    }

    virtual void setColor(int index, sCRGB color) override
    {
        // Set LED to given color, resetting brightness
        // TODO: software brightness as per OutputAdafruitDotStar
        _leds[index].setRGB(color.r, color.g, color.b);
    }

    virtual void setColor(int index, sCRGB color, uint8_t brightness) override
    {
        // Set LED to given color and brightness
        _leds[index].setRGB(color.r, color.g, color.b);
        // TODO: software brightness as per OutputAdafruitDotStar
    }

    virtual void setColor(int index, sCRGB color) override
    {
        // Set LED to given color, keeping brightness
        // TODO: software brightness as per OutputAdafruitDotStar
        _leds[index].setRGB(color.r, color.g, color.b);
    }

private:
    CRGB *_leds; ///< Internal array of LED values
};

#endif
