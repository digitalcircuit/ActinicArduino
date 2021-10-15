Actinic Arduino [![Build Status](https://github.com/digitalcircuit/ActinicArduino/actions/workflows/main.yml/badge.svg)][ci-status-page]
===============

Actinic Arduino provides an interface between strands of LED lights and your computer, primarily intended for the [Actinic lighting controller](https://github.com/digitalcircuit/actinic), but usable by any program that can talk to an Arduino.

## Compatibility
* LED strips
  * [Adafruit DotStars](https://learn.adafruit.com/adafruit-dotstar-leds)
  * Anything the [FastLED library supports](https://github.com/FastLED/FastLED/wiki/Overview#chipsets)
  * [Modified GE G-35 Christmas lights](https://web.archive.org/web/20190322170653/http://www.deepdarc.com/2010/11/27/hacking-christmas-lights/)
* Status indicators
  * Simple LED (most Arduino-compatible microcontrollers)
  * DotStar pixel (e.g. as on the [Adafruit ItsyBitsy M4 Express](https://learn.adafruit.com/introducing-adafruit-itsybitsy-m4))

## Installing

* Configure your hardware in [`device_config.h`](device_config.h)
  * Includes LED strands, status indicator, and button
* *To be done*

## Usage

* *To be done*

## Building

Tools needed:

* Arduino IDE v1.5 or later
  * Tested: Arduino v1.8.8
* One or more of the following Arduino libraries (*place in Arduino sketch directory's 'libraries' folder*)
  * [Adafruit DotStar Library](https://github.com/digitalcircuit/Adafruit_DotStar/tree/ft-hw-limit-brightness)  (*modified [from original](https://github.com/adafruit/Adafruit_DotStar) with [hardware brightness control](https://github.com/adafruit/Adafruit_DotStar/pull/26)*)
  * [FastLED Library](https://github.com/FastLED/FastLED)
  * [G-35 Arduino Library](https://github.com/digitalcircuit/G35ArduinoLibrary) (*modified for slightly better performance*)
* *To be done*

[ci-status-page]: https://github.com/digitalcircuit/ActinicArduino/actions?query=branch%3Amain
