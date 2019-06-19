/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED.h
    @author   ktown
*/
/**************************************************************************/

#ifndef _Adafruit_FeatherOLED_H_
#define _Adafruit_FeatherOLED_H_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**************************************************************************/
/*!
 @brief  Class that extends the SSD1306 to allow easy usage such as displaying
 the battery
 */
/**************************************************************************/
class Adafruit_FeatherOLED : public Adafruit_SSD1306
{
  protected:
    float   _battery;
    bool    _batteryIcon;
    bool    _batteryVisible;

  public:
    enum
    {
      FOLED_BATTERYICON_NONE      = 0,       // Displays volts
      FOLED_BATTERYICON_THREEBAR  = 1
    };

    // Constructor
    Adafruit_FeatherOLED (TwoWire *wire=&Wire, int reset = -1 ) : Adafruit_SSD1306(128, 32, wire, reset)
    {
      _battery            = 0.0F;
      _batteryIcon        = true;
      _batteryVisible     = true;
    }

    void setBattery          ( float vbat )     { _battery = vbat; }
    void setBatteryVisible   ( bool enable )    { _batteryVisible = enable; }
    void setBatteryIcon      ( bool enable )    { _batteryIcon = enable; }

    void init          ( void );
    void clearMsgArea  ( bool update = true );
    void renderBattery    ( void );
};

#endif /* _Adafruit_FeatherOLED_H_ */
