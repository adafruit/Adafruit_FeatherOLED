/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED_WiFi.h
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

#ifndef _Adafruit_FeatherOLED_WiFi_H_
#define _Adafruit_FeatherOLED_WiFi_H_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>

class Adafruit_FeatherOLED_WiFi : public Adafruit_FeatherOLED
{
  private: 
    int rssiToQualityPercentage ( void );

  protected:
    bool    _connected;
    bool    _connectedVisible;
    int     _rssi;
    bool    _rssiIcon;
    bool    _rssiAsPercentage;
    bool    _rssiVisible;
    int32_t _ipAddress;
    bool    _ipAddressVisible;

    void renderRSSI       ( void );
    void renderRSSIIcon   ( void );
    void renderConnected  ( void );
    void renderIPAddress  ( void );

  public:

    // Constructor
    Adafruit_FeatherOLED_WiFi ( int reset = -1 ) : Adafruit_FeatherOLED(reset)
    {
      _connected          = false;
      _connectedVisible   = true;
      _rssi               = -99;
      _rssiIcon           = false;
      _rssiAsPercentage   = false;
      _rssiVisible        = true;
      _ipAddress          = 0;
      _ipAddressVisible   = true;
    }

    void setConnected        ( bool conn )      { _connected = conn; }
    void setConnectedVisible ( bool enable )    { _connectedVisible = enable; }
    void setRSSI             ( int rssi )       { _rssi = rssi; }
    void setRSSIIcon         ( bool enable )    { _rssiIcon = enable; }
    void setRSSIAsPercentage ( bool enable )    { _rssiAsPercentage = enable; }
    void setRSSIVisible      ( bool enable )    { _rssiVisible = enable; }
    void setIPAddress        ( uint32_t addr )  { _ipAddress = addr; }
    void setIPAddressVisible ( bool enable )    { _ipAddressVisible = enable; }
    void refreshIcons  ( void );
};

#endif /* _Adafruit_FeatherOLED_WiFi_H_ */
