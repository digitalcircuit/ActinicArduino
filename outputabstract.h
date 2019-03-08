#ifndef __INC_AA_OUTPUT_ABSTRACT
#define __INC_AA_OUTPUT_ABSTRACT

#include <stdint.h>

#include "color.h"

/**
 * Abstract light output
 */
class OutputAbstract
{
public:
    /**
     * Constructs a new abstract light output
     *
     * @param numLEDs  Number of LEDs
     */
    OutputAbstract(int numLEDs) : _numLEDs(numLEDs)
    {
    }

    /**
     * Gets the number of LEDs
     *
     * @return Number of LEDs
     */
    virtual int getNumLEDs();

    /**
     * Gets whether or not the output device simulates brightness control
     *
     * @return True if software brightness, false if hardware brightness
     */
    virtual bool isSoftwareBrightness() = 0;

    /**
     * Initialize the lights
     */
    virtual void initialize() = 0;

    /**
     * Update the lights with the currently set colors
     */
    virtual void show() = 0;

    /**
     * Gets a color with corrections applied to match the LED deficiencies
     *
     * @return sCRGB color, modified to fit the light strand
     */
    virtual sCRGB getCorrectedColor(sCRGB color);

    /**
     * Sets the LED at index to the given brightness
     *
     * @param index       Index of the chosen LED, starting from 0
     * @param brightness  Brightness in range 0-255, 255 being maximum
     */
    virtual void setBrightness(int index, uint8_t brightness) = 0;

    /**
     * Sets the LED at index to the given color at maximum brightness
     *
     * @param index  Index of the chosen LED, starting from 0
     * @param color  Color as sCRGB
     */
    virtual void setColor(int index, sCRGB color) = 0;

    /**
     * Sets the LED at index to the given color and brightness
     *
     * @param index       Index of the chosen LED, starting from 0
     * @param color       Color as sCRGB
     * @param brightness  Brightness in range 0-255, 255 being maximum
     */
    virtual void setColor(int index, sCRGB color, uint8_t brightness) = 0;

    /**
     * Sets the LED at index to the given color at previous brightness
     *
     * @param index  Index of the chosen LED, starting from 0
     * @param color  Color as sCRGB
     */
    virtual void setHue(int index, sCRGB color) = 0;

    /**
     * Sets all LEDs to the given brightness
     *
     * @param brightness  Brightness in range 0-255, 255 being maximum
     */
    virtual void fillBrightness(uint8_t brightness);

    /**
     * Sets all LEDs to the given color at maximum brightness
     *
     * @param color  Color as sCRGB
     */
    virtual void fillColor(sCRGB color);

    /**
     * Sets all LEDs to the given color and brightness
     *
     * @param color       Color as sCRGB
     * @param brightness  Brightness in range 0-255, 255 being maximum
     */
    virtual void fillColor(sCRGB color, uint8_t brightness);

    /**
     * Sets all LEDs to the given color at previous brightness
     *
     * @param color  Color as sCRGB
     */
    virtual void fillHue(sCRGB color);

private:
    int _numLEDs = {}; ///< Number of LEDs
};

#endif
