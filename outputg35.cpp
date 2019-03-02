#include "outputg35.h"

#include <Arduino.h>

#include "protocol.h"

OutputG35::OutputG35(int numLEDs, int outputPin) :
    OutputAbstract(numLEDs),
    _lights(outputPin, numLEDs)
{
    // Set up the G-35 strand output pin
    pinMode(outputPin, OUTPUT);
    digitalWrite(outputPin, LOW);

    // Initialize arrays
    _light_hue_array = new raw_hue_t[numLEDs];
    _light_intensity_array = new raw_intensity_t[numLEDs];
    for(int i=0; i < numLEDs; ++i) {
        _light_hue_array[i] = COLOR_BLACK;
        _light_intensity_array[i] = G35::MAX_INTENSITY;
    }
}

OutputG35::~OutputG35()
{
    // Clean up arrays
    delete [] _light_hue_array;
    delete [] _light_intensity_array;
}

void OutputG35::initialize()
{
    // Initialize the LED display
    _lights.enumerate();
}

void OutputG35::show()
{
    // Update the LED display
    showInternal(_light_hue_array, _light_intensity_array);
}

void OutputG35::setBrightness(int index, uint8_t brightness)
{
    // Set LED to given brightness, keeping hue
    //The (intensity > MAX_INTENSITY) situation is handled by the G35 library
    _light_intensity_array[index] = brightness;
}

void OutputG35::setColor(int index, sCRGB color)
{
    // Set LED to given color, resetting brightness
    _light_hue_array[index] = convertToG35Color(color);
    _light_intensity_array[index] = Protocol::MAX_BRIGHTNESS;
}

void OutputG35::setColor(int index, sCRGB color, uint8_t brightness)
{
    // Set LED to given color and brightness
    _light_hue_array[index] = convertToG35Color(color);
    // Set brightness
    _light_intensity_array[index] = brightness;
}

void OutputG35::setHue(int index, sCRGB color)
{
    // Set LED to given color, keeping brightness
    _light_hue_array[index] = convertToG35Color(color);
}

color_t OutputG35::convertToG35Color(sCRGB color)
{
    // Convert from a 0-255 value to a 0-15 value
    // Conveniently, this is a shift operation
    return G35::color(color.r >> 4, color.g >> 4, color.b >> 4);
}

void OutputG35::showInternal(raw_hue_t bulb_hue_array[], raw_intensity_t bulb_intensity_array[]) {
    // Set each pixel by address on the underlying output
    for(int i=0; i < getNumLEDs(); ++i) {
        _lights.set_color(i, bulb_intensity_array[i], bulb_hue_array[i]);
    }
}
