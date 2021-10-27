/*!
 * @file     Adafruit_FeatherOLED_SH110X.h
 */

#ifndef _Adafruit_FeatherOLED_SH110X_H_
/*!
 * @brief Adafruit FeatherOLED SH110X H
 */
#define _Adafruit_FeatherOLED_SH110X_H_

#include <Adafruit_FeatherOLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>

/**************************************************************************/
/*!
 @brief  Class that extends the SH110X to allow easy usage such as displaying
 the battery
 */
/**************************************************************************/
class Adafruit_FeatherOLED_SH110X : public Adafruit_SH1107 {
protected:
  float _battery; /*!<  Battery Value */              //
  bool _batteryIcon; /*!<  Display Battery Icon */    //
  bool _batteryVisible; /*!<  Battery Info Visible */ //
#if defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  Adafruit_LC709203F *lc = NULL;
#endif

public:
  /**************************************************************************/
  /*!
   @enum BatteryIconType The Battery Icon Types
   */
  /**************************************************************************/
  enum BatteryIconType {
    FOLED_BATTERYICON_NONE = 0,
    /*!<  Displays volts */                                       //
    FOLED_BATTERYICON_THREEBAR = 1 /*!<  Displays a 3-bar icon */ //
  };

  /**************************************************************************/
  /*!
   @brief  Class Constructor
   @param  wire The Wire object
   @param  reset Perform a Reset on initialization
   */
  /**************************************************************************/
  Adafruit_FeatherOLED_SH110X(TwoWire *wire = &Wire, int reset = -1)
      : Adafruit_SH1107(64, 128, wire, reset) {
    _battery = 0.0F;
    _batteryIcon = true;
    _batteryVisible = true;
  }

  /**************************************************************************/
  /*!
   @brief  Sets the Battery Value
   @param  vbat The Battery Voltage
   */
  /**************************************************************************/
  void setBattery(float vbat) { _battery = vbat; }

  /**************************************************************************/
  /*!
   @brief  Sets the Battery Value Visibility
   @param  enable Is visibility enabled?
   */
  /**************************************************************************/
  void setBatteryVisible(bool enable) { _batteryVisible = enable; }

  /**************************************************************************/
  /*!
   @brief  Sets the Battery Icon Visibility
   @param  enable Is visibility enabled?
   */
  /**************************************************************************/
  void setBatteryIcon(bool enable) { _batteryIcon = enable; }

  float getBatteryVoltage();

  void init(void);
  void clearMsgArea(bool update = true);
  void renderBattery(void);
};

#define BATTTEXT_STARTX 77  ///< Battery Text X Position
#define BATTTEXT_STARTY 0   ///< Battery Text Y Position
#define BATTICON_STARTX 110 ///< Battery Icon X Position
#define BATTICON_STARTY 0   ///< Battery Icon X Position
#define BATTICON_WIDTH 18   ///< Battery Icon Width
#define BATTICON_BARWIDTH3                                                     \
  ((BATTICON_WIDTH - 6) / 3) ///< Battery Icon Bar Width

#endif /* _Adafruit_FeatherOLED_SH110X_H_ */
