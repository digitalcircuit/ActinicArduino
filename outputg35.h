#ifndef __INC_AA_OUTPUT_G35
#define __INC_AA_OUTPUT_G35

#include <stdint.h>

// This aspect of the program makes use of the G35 Arduino library.
// --------
/*
 * G35: An Arduino library for GE Color Effects G-35 holiday lights.
 * Copyright © 2011 The G35 Authors. Use, modification, and distribution are
 * subject to the BSD license as described in the accompanying LICENSE file.
 *
 * See README for complete attributions.
 */
#include <G35String.h>
// NOTE: A modified version is available with reduced timing delays in
// G35String.cpp, which will increase performance by reducing tolerance for
// error.

// This program also takes inspiration from earlier G35 efforts:
// --------
// GE Color Effects Arduino Interface
// by Tom Lee <thomas.j.lee at gmail.com>
// Based on code ported by Scott Harris <scottrharris@gmail.com>
// scottrharris.blogspot.com
// which was in turn based on :

/*!     Christmas Light Control
 **     By Robert Quattlebaum <darco@deepdarc.com>
 **     Released November 27th, 2010
 **
 **     For more information,
 **     see <http://www.deepdarc.com/2010/11/27/hacking-christmas-lights/>.
 **
 **     Originally intended for the ATTiny13, but should
 **     be easily portable to other microcontrollers.
 */

#include "color.h"
#include "outputabstract.h"

/**
 * GE ColorEffects G-35 output
 *
 * NOTE: This is a third-party project, unaffiliated with GE.
 *
 * See https://github.com/sowbug/G35Arduino
 */
class OutputG35 : public OutputAbstract
{
public:
    /**
     * Constructs a new GE ColorEffects G-35 output at the given pin
     *
     * @param numLEDs    Number of LEDs (usually 50, 48, or 36)
     * @param outputPin  Data pin for the LED lights
     */
    OutputG35(int numLEDs, int outputPin);

    /**
     * Destroys the GE ColorEffects G-35 output
     */
    ~OutputG35();

    virtual bool isSoftwareBrightness() override
    {
        // We've got real honest-to-goodness hardware support!
        return false;
    }

    virtual void initialize() override;

    virtual void show() override;

    virtual void setBrightness(int index, uint8_t brightness) override;
    virtual void setColor(int index, sCRGB color) override;
    virtual void setColor(int index, sCRGB color, uint8_t brightness) override;
    virtual void setHue(int index, sCRGB color) override;

private:
    typedef uint16_t raw_hue_t;      ///< Color data type
    typedef uint8_t raw_intensity_t; ///< Brightness data type

    /**
     * Converts a sCRGB color to a packed G35 color
     *
     * @param sCRGB  sCRGB color value
     * @return G35 packed color
     */
    color_t convertToG35Color(sCRGB color);

    /**
     * Sequentially sends the hue and intensity arrays to the G-35 light string
     *
     * @param bulb_hue_array        Array of G35 colors
     * @param bulb_intensity_array  Array of brightness values
     */
    void showInternal(raw_hue_t bulb_hue_array[], raw_intensity_t bulb_intensity_array[]);

    G35String _lights;                       ///< Internal G35 string
    raw_hue_t *_light_hue_array;             ///< Software color tracking
    raw_intensity_t *_light_intensity_array; ///< Software brightness tracking
};

#endif
