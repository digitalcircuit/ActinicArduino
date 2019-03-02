#include "outputabstract.h"

int OutputAbstract::getNumLEDs()
{
    return _numLEDs;
}

sCRGB OutputAbstract::getCorrectedColor(sCRGB color)
{
    // Apply the default color correction
    // FastLED/color.h, typical: 255, 176, 240
    return sCRGB(color.r, color.g * 0.69, color.b * 0.94);
}

void OutputAbstract::fillBrightness(uint8_t brightness)
{
    // Fill all LEDs with a given brightness
    for (int i = 0; i < _numLEDs; ++i) {
        setBrightness(i, brightness);
    }
}

void OutputAbstract::fillColor(sCRGB color)
{
    // Fill all LEDs with a given color, resetting brightness
    for (int i = 0; i < _numLEDs; ++i) {
        setColor(i, color);
    }
}

void OutputAbstract::fillColor(sCRGB color, uint8_t brightness)
{
    // Fill all LEDs with a given color and brightness
    for (int i = 0; i < _numLEDs; ++i) {
        setColor(i, color, brightness);
    }
}

void OutputAbstract::fillHue(sCRGB color)
{
    // Fill all LEDs with a given color, keeping brightness
    for (int i = 0; i < _numLEDs; ++i) {
        setHue(i, color);
    }
}
