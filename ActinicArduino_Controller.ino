/* Actinic: Compilation of amazing work done by others
    Some modifications in order to be more useful with the companion C# Actinic program, built
    by Shane Synan <digitalcircuit36939@gmail.com>

    -- Added an automatic switch to a test-mode if no serial input is received in an amount of time
    -- Added a batch-update mode to modify both color and hue at once
    -- Added output string on startup to identify firmware on Arduino
    -- Fixed an input overflow issue with Arduino claiming to be ready for new input before finishing the prior command
    -- Reduced timing delays in G35String.cpp in order to increase performance
 */

/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
 Copyright © 2011 The G35 Authors. Use, modification, and distribution are
 subject to the BSD license as described in the accompanying LICENSE file.

 See README for complete attributions.
 */

#include <G35String.h>

// Total # of lights on string (usually 50, 48, or 36). Maximum is 63, because
// the protocol uses 6-bit addressing and bulb #63 is reserved for broadcast
// messages.
#define LIGHT_COUNT (50)

// Copied from G35String.cpp since it's not defined in the header - update here if needed
#define G35_DELAYLONG 6    // should be ~ 20uS long
#define G35_DELAYSHORT 2   // should be ~ 10uS long
#define G35_DELAYEND 40     // should be ~ 30uS long
// Specifies expected delay in milliseconds to update all lights.
// Calculated from the constants defined in G35String.h, with additional delay
// added to account for processing time.
//
// You can measure real latency with Actinic by defining DEBUG_USB_PERFORMANCE in ArduinoOutput.cs
// (Below assumes about a factor of four increase for each light - x3.85.  It's not quite 4.)
const int AVERAGE_LATENCY = ((G35_DELAYSHORT + (G35_DELAYLONG + G35_DELAYSHORT)*26 + G35_DELAYEND) * 0.001)*LIGHT_COUNT*3.85;

// Arduino pin number. Pin 13 will blink the on-board LED.
#define STATUS_PIN (13)
#define G35_PIN (8)

G35String lights(G35_PIN, LIGHT_COUNT);

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

//#define xmas_color_t uint16_t // typedefs can cause trouble in the Arduino environment  

uint16_t light_hue_array[LIGHT_COUNT];
uint8_t light_intensity_array[LIGHT_COUNT];

void xmas_reflect_array(uint16_t bulb_hue_array[], uint8_t bulb_intensity_array[]) {
  for(int i=0;i<LIGHT_COUNT;i++) {
    lights.set_color(i, bulb_intensity_array[i], bulb_hue_array[i]);
  }
}

const unsigned int IDLE_TIME = 5 * 1000;
unsigned long lastCommandTime = 0;
boolean commandSent = false;
boolean idleMode = false;

boolean changed = false;

void setup() {
  pinMode(STATUS_PIN, OUTPUT);
  pinMode(G35_PIN, OUTPUT);
  digitalWrite(STATUS_PIN, LOW);
  digitalWrite(G35_PIN, LOW);

  Serial.begin(115200);

  for(int i=0;i<LIGHT_COUNT;i++) {
    light_hue_array[i] = COLOR_BLACK;
    light_intensity_array[i] = G35::MAX_INTENSITY;
  }

  lights.enumerate();
  lights.fill_color(0, LIGHT_COUNT, G35::MAX_INTENSITY, COLOR_BLACK);

  digitalWrite(STATUS_PIN, LOW);
  // Firmware version and hardware information, used by Actinic to automatically detect controllers
  // Use F() to use PROGMEM instead of wasting SRAM
  Serial.println(F("ActinicArduino_Controller:2.0"));
  Serial.print(F("light_count:"));
  Serial.println (LIGHT_COUNT);
  Serial.print(F("color_max:"));
  Serial.println (CHANNEL_MAX);
  Serial.print(F("bright_max:"));
  Serial.println (G35::MAX_INTENSITY);
  Serial.print(F("avg_latency:"));
  Serial.println (AVERAGE_LATENCY);
  Serial.println(F("end_init"));
}

void loop() {

  if(Serial.available()>0) {
    // Hue, intensity, or both?
    char command = Serial.read();
    if (command=='I') {
      digitalWrite(STATUS_PIN, HIGH);

      // read the intensity data & assign it
      for(int i=0;i<LIGHT_COUNT;i++) {
        while(Serial.available() < 1) {
        }
        light_intensity_array[i] = Serial.read();
        //The (intensity > MAX_INTENSITY) situation is handled by the G35 library
      }
      changed = true;
      commandSent = true;
      lastCommandTime = millis();
    } else if(command=='H') {
      digitalWrite(STATUS_PIN, HIGH);

      // read the hue data and assign it
      for(int i=0;i<(LIGHT_COUNT);i++) {
        while(Serial.available() < 3) {
        }
        light_hue_array[i] = G35::color(Serial.read(), Serial.read(), Serial.read()); 
      }
      changed = true;
      commandSent = true;
      lastCommandTime = millis();
    } else if(command=='A') {
      digitalWrite(STATUS_PIN, HIGH);

      // read the color and hue data, then assign it
      for(int i=0;i<(LIGHT_COUNT);i++) {
        while(Serial.available() < 4) {
        }
        light_hue_array[i] = G35::color(Serial.read(), Serial.read(), Serial.read());
        light_intensity_array[i] = Serial.read();
      }
      changed = true;
      commandSent = true;
      lastCommandTime = millis();
    }
  }

  if(changed) {
    xmas_reflect_array(light_hue_array, light_intensity_array);
    Serial.println('#');
    // Shane: don't acknowledge the write until the LEDs have been updated
    digitalWrite(STATUS_PIN, LOW);
    changed = false;
  }

  if (commandSent == false) {
    if ((millis() - lastCommandTime) > IDLE_TIME) {
      if (idleMode == false) {
        idleMode = true;

        digitalWrite(STATUS_PIN, HIGH);
        for (int selectedBrightness = 0; selectedBrightness <= G35::MAX_INTENSITY; selectedBrightness += 3) { 
          lights.fill_color(0, LIGHT_COUNT, selectedBrightness, COLOR_ORANGE);
        }

        lights.do_test_patterns();
        lights.fill_color(0, LIGHT_COUNT, G35::MAX_INTENSITY, COLOR_ORANGE);

        lights.set_color(0, G35::MAX_INTENSITY, COLOR_RED);
        lights.set_color(1, G35::MAX_INTENSITY, COLOR_YELLOW);

        lights.set_color((LIGHT_COUNT / 2) - 2, G35::MAX_INTENSITY, COLOR_YELLOW);
        lights.set_color((LIGHT_COUNT / 2) - 1, G35::MAX_INTENSITY, COLOR_PURPLE);
        lights.set_color((LIGHT_COUNT / 2), G35::MAX_INTENSITY, COLOR_BLUE);
        lights.set_color((LIGHT_COUNT / 2) + 1, G35::MAX_INTENSITY, COLOR_YELLOW);

        lights.set_color(LIGHT_COUNT - 2, G35::MAX_INTENSITY, COLOR_YELLOW);
        lights.set_color(LIGHT_COUNT - 1, G35::MAX_INTENSITY, COLOR_GREEN);
        digitalWrite(STATUS_PIN, LOW);

      }
    }
    if (commandSent == true & idleMode == true) {
      idleMode = false;
    }
  }

  interrupts();
}
