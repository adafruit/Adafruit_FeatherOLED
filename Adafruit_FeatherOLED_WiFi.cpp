/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED_WiFi.cpp
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
#include "Adafruit_FeatherOLED_WiFi.h"

/******************************************************************************/
/*!
    @brief  Renders the RSSI icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderRSSI( void )
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
void Adafruit_FeatherOLED_WiFi::renderConnected ( void )
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
void Adafruit_FeatherOLED_WiFi::renderIPAddress ( void )
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
    @brief  Updates the OLED display
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::refreshIcons ( void )
{
  fillRect(0, 0, 128, 8, BLACK);
  fillRect(0, 24, 128, 8, BLACK);
  renderBattery();
  renderRSSI();
  renderConnected();
  renderIPAddress();
  display();
}
