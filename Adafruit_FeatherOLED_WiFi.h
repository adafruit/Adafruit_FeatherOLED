/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED_WiFi.h
    @author   ktown
*/
/**************************************************************************/

#ifndef _Adafruit_FeatherOLED_WiFi_H_
#define _Adafruit_FeatherOLED_WiFi_H_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>

/**************************************************************************/
/*!
 @brief  Class that extends Adafruit_FeatherOLED to help with some WiFi related
 helper functions
 */
/**************************************************************************/
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
    Adafruit_FeatherOLED_WiFi (TwoWire *wire=&Wire, int reset = -1 ) : Adafruit_FeatherOLED(wire, reset)
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

#define RSSITEXT_STARTX      14 ///< RSSI Text X Position
#define RSSITEXT_STARTY      0  ///< RSSI Text Y Position
#define RSSIICON_STARTX      0  ///< RSSI Icon X Position
#define RSSIICON_STARTY      4  ///< RSSI Icon Y Position
#define RSSIICON_STARTHEIGHT 3  ///< RSSI Icon Height
#define RSSIICON_BARWIDTH    2  ///< RSSI Icon Width

#endif /* _Adafruit_FeatherOLED_WiFi_H_ */
