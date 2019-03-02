Actinic Arduino
===============

Actinic Arduino provides an interface between strands of LED lights and your computer, primarily intended for the [Actinic lighting controller][actinic], but usable by any program that can talk to an Arduino.

## Compatibility
* LED strips
  * [Adafruit DotStars][adafruit_dotstar_learn]
  * Anything the [FastLED library supports][fastled_support]
  * [Modified GE G-35 Christmas lights][g35arduino_mod_blog]
* Status indicators
  * Simple LED (most Arduino-compatible microcontrollers)
  * DotStar pixel (e.g. as on the [Adafruit ItsyBitsy M4 Express][adafruit_itsybitsy_m4_learn])

## Installing

* Configure your hardware in [`device_config.h`][device_config]
  * Includes LED strands, status indicator, and button
* *To be done*

## Usage

* *To be done*

## Building

Tools needed:

* Arduino IDE v1.5 or later
  * Tested: Arduino v1.8.8
* One or more of the following Arduino libraries (*place in Arduino sketch directory's 'libraries' folder*)
  * [Adafruit DotStar Library][adafruit_dotstar_gh]
  * [FastLED Library][fastled_gh]
  * [G-35 Arduino Library][g35arduino_mod_gh] (*modified for slightly better performance*)
* *To be done*

[actinic]: https://github.com/digitalcircuit/actinic
[adafruit_dotstar_learn]: https://learn.adafruit.com/adafruit-dotstar-leds
[adafruit_dotstar_gh]: https://github.com/adafruit/Adafruit_DotStar
[adafruit_itsybitsy_m4_learn]: https://learn.adafruit.com/introducing-adafruit-itsybitsy-m4
[fastled_gh]: https://github.com/FastLED/FastLED
[fastled_support]: https://github.com/FastLED/FastLED/wiki/Overview#chipsets
[g35arduino_mod_blog]: http://www.deepdarc.com/2010/11/27/hacking-christmas-lights/
[g35arduino_mod_gh]: https://github.com/digitalcircuit/G35ArduinoLibrary
[device_config]: device_config.h
