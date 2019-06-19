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
    float   _battery;           /*!<  Battery Value *///
    bool    _batteryIcon;       /*!<  Display Battery Icon *///
    bool    _batteryVisible;    /*!<  Battery Info Visible *///

  public:
    /**************************************************************************/
    /*!
     @enum BatteryIconType The Battery Icon Types
     */
    /**************************************************************************/
    enum BatteryIconType
    {
      FOLED_BATTERYICON_NONE      = 0,         /*!<  Displays volts *///
      FOLED_BATTERYICON_THREEBAR  = 1          /*!<  Displays a 3-bar icon *///
    };

    /**************************************************************************/
    /*!
     @brief  Class Constructor
     @param  wire The Wire object
     @param  reset Perform a Reset on initialization
     */
    /**************************************************************************/
    Adafruit_FeatherOLED (TwoWire *wire=&Wire, int reset = -1 ) : Adafruit_SSD1306(128, 32, wire, reset)
    {
      _battery            = 0.0F;
      _batteryIcon        = true;
      _batteryVisible     = true;
    }

    /**************************************************************************/
    /*!
     @brief  Sets the Battery Value
     @param  vbat The Battery Voltage
     */
    /**************************************************************************/
    void setBattery          ( float vbat )     { _battery = vbat; }

    /**************************************************************************/
    /*!
     @brief  Sets the Battery Value Visibility
     @param  enable Is visibility enabled?
     */
    /**************************************************************************/
    void setBatteryVisible   ( bool enable )    { _batteryVisible = enable; }

    /**************************************************************************/
    /*!
     @brief  Sets the Battery Icon Visibility
     @param  enable Is visibility enabled?
     */
    /**************************************************************************/
    void setBatteryIcon      ( bool enable )    { _batteryIcon = enable; }

    void init          ( void );
    void clearMsgArea  ( bool update = true );
    void renderBattery    ( void );
};

#define BATTTEXT_STARTX     77  ///< Battery Text X Position
#define BATTTEXT_STARTY     0   ///< Battery Text Y Position
#define BATTICON_STARTX     110 ///< Battery Icon X Position
#define BATTICON_STARTY     0   ///< Battery Icon X Position
#define BATTICON_WIDTH      18  ///< Battery Icon Width
#define BATTICON_BARWIDTH3  ((BATTICON_WIDTH - 6) / 3) ///< Battery Icon Bar Width

#endif /* _Adafruit_FeatherOLED_H_ */
