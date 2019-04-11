#include "outputadafruitdotstar.h"

#include "protocol.h"

// Include hardware SPI interface if available
// Matches Adafruit_DotStar library include
#if !defined(__AVR_ATtiny85__)
 #include <SPI.h>
#endif

OutputAdafruitDotStar::OutputAdafruitDotStar(int numLEDs, uint8_t rgbOrder, uint32_t clockMaxOverride) :
    OutputAbstract(numLEDs),
    _lights(numLEDs, rgbOrder),
    _clockMaxOverride(clockMaxOverride)
{
    initializeArrays(numLEDs);
}

OutputAdafruitDotStar::OutputAdafruitDotStar(int numLEDs, uint8_t rgbOrder, int dataPin, int clockPin) :
    OutputAbstract(numLEDs),
    _lights(numLEDs, dataPin, clockPin, rgbOrder)
{
    initializeArrays(numLEDs);
}

OutputAdafruitDotStar::~OutputAdafruitDotStar()
{
    // Clean up arrays
    delete [] _light_intensity_array;
}

void OutputAdafruitDotStar::initialize()
{
    // Initialize the LED display
    _lights.begin();

    // Check if platform has SPI transaction support
    #if defined(SPI_HAS_TRANSACTION)
        if (_clockMaxOverride > 0) {
            // Custom SPI clock speed specified, override default using
            // begin/end transaction.
            //
            // The other parameters are copied from the Adafruit_DotStar
            // library hardware SPI initialization; update here if changed
            // there.
            SPI.beginTransaction(
                SPISettings(_clockMaxOverride, MSBFIRST, SPI_MODE0)
            );
            SPI.endTransaction();
            // This will need changed once the Adafruit library is adapted to
            // use transactions.
        }
    #endif
}

void OutputAdafruitDotStar::show()
{
    // Update the LED display
    _lights.show();
}

void OutputAdafruitDotStar::setBrightness(int index, uint8_t brightness)
{
    // Set LED to given brightness, keeping hue
    // Simulate brightness control by calculating the ratio to go from the
    // previous brightness to the new brightness.
    // Example: old_color × 1 ÷ (old_brightness ÷ new_brightness)
    // ...with old of 255, new of 2, color of 128, this results in 1
    float brightnessRatio = 1 / (_light_intensity_array[index] / (float)(brightness));
    _light_intensity_array[index] = brightness;
    sCRGB existingColor(_lights.getPixelColor(index));
    _lights.setPixelColor(
        index,
        existingColor.r * brightnessRatio,
        existingColor.g * brightnessRatio,
        existingColor.b * brightnessRatio
    );
}

void OutputAdafruitDotStar::setColor(int index, sCRGB color)
{
    // Set LED to given color, resetting brightness
    _light_intensity_array[index] = Protocol::MAX_BRIGHTNESS;
    _lights.setPixelColor(index, color.r, color.g, color.b);
}

void OutputAdafruitDotStar::setColor(int index, sCRGB color, uint8_t brightness)
{
    // Set LED to given color and brightness
    // Simulate brightness control by dividing by the new brightness.
    float brightnessRatio = brightness / (float)Protocol::MAX_BRIGHTNESS;
    _light_intensity_array[index] = brightness;
    _lights.setPixelColor(index, color.r * brightnessRatio, color.g * brightnessRatio, color.b * brightnessRatio);
}

void OutputAdafruitDotStar::setHue(int index, sCRGB color)
{
    // Set LED to given color, keeping brightness
    // Simulate brightness control by dividing by the existing brightness.
    float brightnessRatio = _light_intensity_array[index] / (float)Protocol::MAX_BRIGHTNESS;
    _lights.setPixelColor(index, color.r * brightnessRatio, color.g * brightnessRatio, color.b * brightnessRatio);
}

void OutputAdafruitDotStar::initializeArrays(int numLEDs)
{
    // Initialize arrays
    _light_intensity_array = new raw_intensity_t[numLEDs];
    for(int i=0; i < numLEDs; ++i) {
        _light_intensity_array[i] = Protocol::MAX_BRIGHTNESS;
    }
}
