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
    @brief  Converts RSSI from dBm to quality percentage
*/
/******************************************************************************/
int Adafruit_FeatherOLED_WiFi::rssiToQualityPercentage( void )
{
  int quality;
  if(_rssi <= -100)
  {
    quality = 0;
  }
  else if(_rssi >= -50)
  {
    quality = 100;
  }
  else
  {
    quality = 2 * (_rssi + 100);
  } 

  return quality;
}

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

    if (_connected)
    {
      renderRSSIIcon();

      if(_rssiAsPercentage)
      {
        int quality = rssiToQualityPercentage();
        if(quality == 0)
        {
          print("---");
        }
        else
        {
          char buf[5];
          itoa(quality, buf, 10);
          strcat(buf, "%");
          print(buf);
        }
      }
      else
      {
        print(_rssi);
        print(" dBm");
      }
    }
    else
    {
      print("RSSI:");
      print("---");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the WiFi icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderRSSIIcon ( void )
{
  #define RSSITEXT_STARTX      14
  #define RSSITEXT_STARTY      0
  #define RSSIICON_STARTX      0
  #define RSSIICON_STARTY      4
  #define RSSIICON_STARTHEIGHT 3
  #define RSSIICON_BARWIDTH    2

  if(_rssiIcon)
  {
    int quality = rssiToQualityPercentage();
    if(quality == 0)
    {
      print("---");
    }
    else
    {
      // Render the first bar if there is any signal at all
      fillRect(RSSIICON_STARTX, 
               RSSIICON_STARTY,
               RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT,
               WHITE);
    }

    // Render the second bar
    if(quality >= 45)
    {
      fillRect(RSSIICON_STARTX + 3, 
               RSSIICON_STARTY - 1,
               RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT + 1,
               WHITE);      
    }

    // Render the third bar
    if(quality >= 70)
    {
      fillRect(RSSIICON_STARTX + 6, 
               RSSIICON_STARTY - 2,
               RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT + 2,
               WHITE);      
    }

    // Render the fourth bar. The most coveted of all bars.
    if(quality >= 90)
    {
      fillRect(RSSIICON_STARTX + 9, 
               RSSIICON_STARTY - 4,
               RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT + 4,
               WHITE);
    }

    setCursor(RSSITEXT_STARTX, RSSITEXT_STARTY);
  }
  else
  {
    print("RSSI:");
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
      print(_ipAddress & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 8) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 16) & 0xFF, DEC);
      print(".");
      print((_ipAddress >> 24) & 0xFF, DEC);
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
