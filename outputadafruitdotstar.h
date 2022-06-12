#ifndef __INC_AA_OUTPUT_ADAFRUIT_DOTSTAR
#define __INC_AA_OUTPUT_ADAFRUIT_DOTSTAR

#include <stdint.h>

#include <Adafruit_DotStar.h>

#include "color.h"
#include "outputabstract.h"

/**
 * Adafruit DotStar output
 *
 * NOTE: This is a third-party project, unaffiliated with Adafruit.
 *
 * See https://learn.adafruit.com/adafruit-dotstar-leds
 */
class OutputAdafruitDotStar : public OutputAbstract
{
public:
    /**
     * Constructs a new Adafruit DotStar output using hardware SPI, fixed pins
     *
     * @param numLEDs           Number of DotStar pixels
     * @param rgbOrder          RGB ordering of pixels, e.g. DOTSTAR_BGR
     */
    OutputAdafruitDotStar(int numLEDs, uint8_t rgbOrder);

    /**
     * Constructs a new Adafruit DotStar output using software SPI, custom pins
     *
     * @param numLEDs   Number of DotStar pixels
     * @param rgbOrder  RGB ordering of pixels, e.g. DOTSTAR_BGR
     * @param dataPin   Data pin of the DotStar strip
     * @param clockPin  Clock pin of the DotStar strip
     */
    OutputAdafruitDotStar(int numLEDs, uint8_t rgbOrder, int dataPin, int clockPin);

    /**
     * Destroys the Adafruit DotStar output
     */
    ~OutputAdafruitDotStar();

    virtual bool isSoftwareBrightness() override
    {
        // TODO: add support for hardware brightness control
        // This requires modifications to the Adafruit DotStar library to track
        // and send per-pixel brightness.  For a starting point, see...
        // https://github.com/adafruit/Adafruit_DotStar/pull/26
        return true;
    }

    virtual void initialize() override;

    virtual void show() override;

    virtual void setBrightness(int index, uint8_t brightness) override;
    virtual void setColor(int index, sCRGB color) override;
    virtual void setColor(int index, sCRGB color, uint8_t brightness) override;
    virtual void setHue(int index, sCRGB color) override;

private:
    typedef uint8_t raw_intensity_t; ///< Brightness data type

    /**
     * Initializes the internal arrays
     */
    void initializeArrays(int numLEDs);

    Adafruit_DotStar _lights;                ///< Internal DotStar strip
    raw_intensity_t *_light_intensity_array; ///< Software brightness tracking
};

#endif
