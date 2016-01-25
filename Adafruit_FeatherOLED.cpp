/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED.cpp
    @author   ktown

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include "Adafruit_FeatherOLED.h"

/******************************************************************************/
/*!
    @brief  Renders the battery icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED::renderBattery ( void )
{
  #define BATTTEXT_STARTX     77
  #define BATTTEXT_STARTY     0
  #define BATTICON_STARTX     110
  #define BATTICON_STARTY     0
  #define BATTICON_WIDTH      18
  #define BATTICON_BARWIDTH3  ((BATTICON_WIDTH - 6) / 3)

  if (_batteryVisible)
  {
    // Render the voltage in text
    setCursor(BATTTEXT_STARTX, BATTTEXT_STARTY);
    print(_battery, 2);
    println("V");

    // Render the battery icon if requested
    if (_batteryIcon)
    {
      // Draw the base of the battery
      drawLine( BATTICON_STARTX + 1,
                BATTICON_STARTY,
                BATTICON_STARTX + BATTICON_WIDTH - 4,
                BATTICON_STARTY,
                WHITE);
      drawLine( BATTICON_STARTX,
                BATTICON_STARTY + 1,
                BATTICON_STARTX,
                BATTICON_STARTY + 5,
                WHITE);
      drawLine( BATTICON_STARTX + 1,
                BATTICON_STARTY + 6,
                BATTICON_STARTX + BATTICON_WIDTH - 4,
                BATTICON_STARTY + 6,
                WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 3,
                BATTICON_STARTY + 1,
                WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 2,
                BATTICON_STARTY + 1,
                WHITE);
      drawLine( BATTICON_STARTX + BATTICON_WIDTH - 1,
                BATTICON_STARTY + 2,
                BATTICON_STARTX + BATTICON_WIDTH - 1,
                BATTICON_STARTY + 4,
                WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 2,
                BATTICON_STARTY + 5,
                WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 3,
                BATTICON_STARTY + 5,
                WHITE);
      drawPixel(BATTICON_STARTX + BATTICON_WIDTH - 3,
                BATTICON_STARTY + 6,
                WHITE);

      // Draw the appropriate number of bars
      if (_battery > 4.26F)
      {
        // USB (Solid Rectangle)
        fillRect(BATTICON_STARTX + 2,     // X
                 BATTICON_STARTY + 2,     // Y
                 BATTICON_BARWIDTH3 * 3,  // W
                 3,                       // H
                 WHITE);
      }
      else if ((_battery <= 4.26F) && (_battery >= 4.1F))
      {
        // Three bars
        for (uint8_t i = 0; i < 3; i++)
        {
          fillRect(BATTICON_STARTX + 2 + (i * BATTICON_BARWIDTH3),
                   BATTICON_STARTY + 2,
                   BATTICON_BARWIDTH3 - 1,
                   3,
                   WHITE);
        }
      }
      else if ((_battery < 4.1F) && (_battery >= 3.8F))
      {
        // Two bars
        for (uint8_t i = 0; i < 2; i++)
        {
          fillRect(BATTICON_STARTX + 2 + (i * BATTICON_BARWIDTH3),
                   BATTICON_STARTY + 2,
                   BATTICON_BARWIDTH3 - 1,
                   3,
                   WHITE);
        }
      }
      else if ((_battery < 3.8F) && (_battery >= 3.4F))
      {
        // One bar
        fillRect(BATTICON_STARTX + 2,
                 BATTICON_STARTY + 2,
                 BATTICON_BARWIDTH3 - 1,
                 3,
                 WHITE);
      }
      else
      {
        // No bars
      }
    }
  }
}

/******************************************************************************/
/*!
    @brief  Initialises the display (always call this first!)
*/
/******************************************************************************/
void Adafruit_FeatherOLED::init ( void )
{
  // Generate the high voltage from the 3.3v line internally and
  // initialize with the I2C addr 0x3C (for the 128x32)
  begin(SSD1306_SWITCHCAPVCC, 0x3C);
  setTextSize(1);
  setTextColor(WHITE);
  clearDisplay();
}

/******************************************************************************/
/*!
    @brief  Clears the message area (the middle 128x16 pixels) and sets the
            cursor to 0, 8
*/
/******************************************************************************/
void Adafruit_FeatherOLED::clearMsgArea ( void )
{
  fillRect(0, 8, 128, 16, BLACK);
  setCursor(0, 8);
  display();
}
