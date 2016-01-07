/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLD.cpp
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
  if (_batteryVisible)
  {
    if (_batteryIcon)
    {
      // Display the battery icon
    }
    else
    {
      // Render the voltage in text
      setCursor(96,0);
      print(_battery, 2);
      println("V");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the RSSI icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED::renderRSSI( void )
{
  if (_rssiVisible)
  {
    setCursor(0,0);
    print("RSSI:");
    if (_connected)
    {
      print(_rssi);
    }
    else
    {
      print("---");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the connection status icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED::renderConnected ( void )
{
  if (_connectedVisible)
  {
    setCursor(100,24);
    if (_connected)
    {
      println("CONN");
    }
    else
    {
      println("----");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the connection status icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED::renderIPAddress ( void )
{
  if (_ipAddressVisible)
  {
    if (_connected)
    {
      setCursor(0,24);
      print((_ipAddress >> 24) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 16) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 8) & 0xFF, DEC);
      print(".");
      print(_ipAddress & 0xFF, DEC);
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
    @brief  Updates the OLED display
*/
/******************************************************************************/
void Adafruit_FeatherOLED::refreshIcons ( void )
{
  clearDisplay();
  renderBattery();
  renderRSSI();
  renderConnected();
  renderIPAddress();
  display();
}
