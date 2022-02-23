/*!
 * @file     Adafruit_FeatherOLED_SH110X.cpp
 *
 * @author   ktown
 *
 *
 * @section intro_sec_SH110X Introduction
 *
 * Helper class to work with 128x64 OLED displays on Adafruit Feathers
 * Tested and works great with the Adafruit OLED FeatherWing - 128x64:
 * http://www.adafruit.com/products/4650
 *
 * @section LICENSE_SH110X
 *
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2016, Adafruit Industries (adafruit.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "Adafruit_FeatherOLED_SH110X.h"

/*!
  @brief  Renders the battery icon
*/
void Adafruit_FeatherOLED_SH110X::renderBattery(void) {
  if (_batteryVisible) {
    // Render the voltage in text
    setCursor(BATTTEXT_STARTX, BATTTEXT_STARTY);
    print(_battery, 2);
    println("V");

    // Render the battery icon if requested
    if (_batteryIcon) {
      // Draw the base of the battery
      drawLine(BATTICON_STARTX + 1, BATTICON_STARTY,
               BATTICON_STARTX + BATTICON_WIDTH - 4, BATTICON_STARTY,
               SH110X_WHITE);
      drawLine(BATTICON_STARTX, BATTICON_STARTY + 1, BATTICON_STARTX,
               BATTICON_STARTY + 5, SH110X_WHITE);
      drawLine(BATTICON_STARTX + 1, BATTICON_STARTY + 6,
               BATTICON_STARTX + BATTICON_WIDTH - 4, BATTICON_STARTY + 6,
               SH110X_WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 3, BATTICON_STARTY + 1,
                SH110X_WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 2, BATTICON_STARTY + 1,
                SH110X_WHITE);
      drawLine(BATTICON_STARTX + BATTICON_WIDTH - 1, BATTICON_STARTY + 2,
               BATTICON_STARTX + BATTICON_WIDTH - 1, BATTICON_STARTY + 4,
               SH110X_WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 2, BATTICON_STARTY + 5,
                SH110X_WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 3, BATTICON_STARTY + 5,
                SH110X_WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 3, BATTICON_STARTY + 6,
                SH110X_WHITE);

      // Draw the appropriate number of bars
      if (_battery > 4.26F) {
        // USB (Solid Rectangle)
        fillRect(BATTICON_STARTX + 2,    // X
                 BATTICON_STARTY + 2,    // Y
                 BATTICON_BARWIDTH3 * 3, // W
                 3,                      // H
                 SH110X_WHITE);
      } else if ((_battery <= 4.26F) && (_battery >= 4.1F)) {
        // Three bars
        for (uint8_t i = 0; i < 3; i++) {
          fillRect(BATTICON_STARTX + 2 + (i * BATTICON_BARWIDTH3),
                   BATTICON_STARTY + 2, BATTICON_BARWIDTH3 - 1, 3,
                   SH110X_WHITE);
        }
      } else if ((_battery < 4.1F) && (_battery >= 3.8F)) {
        // Two bars
        for (uint8_t i = 0; i < 2; i++) {
          fillRect(BATTICON_STARTX + 2 + (i * BATTICON_BARWIDTH3),
                   BATTICON_STARTY + 2, BATTICON_BARWIDTH3 - 1, 3,
                   SH110X_WHITE);
        }
      } else if ((_battery < 3.8F) && (_battery >= 3.4F)) {
        // One bar
        fillRect(BATTICON_STARTX + 2, BATTICON_STARTY + 2,
                 BATTICON_BARWIDTH3 - 1, 3, SH110X_WHITE);
      } else {
        // No bars
      }
    }
  }
}

/*!
 * @brief  Initialises the display (always call this first!)
 */
void Adafruit_FeatherOLED_SH110X::init(void) {
  // Generate the high voltage from the 3.3v line internally and
  // initialize with the I2C addr 0x3C (for the 128x64)
  begin(0x3C, true);
  setRotation(1);
  setTextSize(1);
  setTextColor(SH110X_WHITE);
  clearDisplay();

#if defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  lc = new Adafruit_LC709203F();
  if (!lc || !lc->begin()) {
    lc = NULL;
    return;
  }
  lc->setPackSize(LC709203F_APA_500MAH);
  lc->setAlarmVoltage(3.8);
#endif
}

/*!
  @brief  Clears the message area (the middle 128x16 pixels) and sets the cursor
  to 0, 8
  @param  update Automatically update the display after clearing
*/
void Adafruit_FeatherOLED_SH110X::clearMsgArea(bool update) {
  fillRect(0, 8, 128, 16, SH110X_BLACK);
  setCursor(0, 8);
  if (update) {
    display();
  }
}

/**************************************************************************/
/*!
  @brief   Query the Feather for the Lipoly battery voltage
  @returns The battery voltage in volts
*/
/**************************************************************************/
float Adafruit_FeatherOLED_SH110X::getBatteryVoltage() {
#if defined(ARDUINO_FEATHER52)
  int raw;

  // Set the analog reference to 3.0V (default = 3.6V)
  analogReference(AR_INTERNAL_3_0);

  // Set the resolution to 12-bit (0..4095)
  analogReadResolution(12); // Can be 8, 10, 12 or 14

  // Let the ADC settle
  delay(1);

  // Get the raw 12-bit, 0..3000mV ADC value
  raw = analogRead(VBATPIN);

  // Set the ADC back to the default settings
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  // Convert the raw value to compensated mv, taking the resistor-
  // divider into account (providing the actual LIPO voltage)
  // ADC range is 0..3000mV and resolution is 12-bit (0..4095),
  return ((float)raw * REAL_VBAT_MV_PER_LSB) / 1000.0;
#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  if (!lc)
    return 0;
  return lc->cellVoltage();
#else
  return analogRead(VBATPIN) * VBAT_MULTIPLIER;
#endif
}
