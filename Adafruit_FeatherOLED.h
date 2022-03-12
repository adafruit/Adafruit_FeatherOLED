/*!
 * @file     Adafruit_FeatherOLED.h
 */

#ifndef _Adafruit_FeatherOLED_H_
/*!
 * @brief Adafruit FeatherOLED H
 */
#define _Adafruit_FeatherOLED_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#if defined(__SAMD51__)
// m4 feathers
#define VBATPIN A6
#define VBAT_MULTIPLIER 2.0 * 3.3 / 1024.0

#elif defined(ARDUINO_ARCH_SAMD)
// m0 feathers
#define VBATPIN A7
#define VBAT_MULTIPLIER 2.0 * 3.3 / 1024.0

#elif defined(__AVR_ATmega32U4__)
// 32u4 feather
#define VBATPIN A9
#define VBAT_MULTIPLIER 2.0 * 3.3 / 1024.0

#elif defined(ESP8266)
// esp8266 feather
#define VBATPIN A0
/*
 * The ESP8266 Feather Huzzah does not have an internal voltage divider, so you
 * must build one. However, the voltage on the Analog Input must be between
 * 0-1.0V or you could risk damaging the chip. So please keep this in mind when
 * selecting resistor values. For the default values you could use a 100K
 * resistor between ADC and the BAT pin (RESISTOR_BAT) and a 10K Resistor
 * between ADC and Ground (RESISTOR_GND) or change the values below for other
 * combinations.
 */
#define RESISTOR_BAT 100000
#define RESISTOR_GND 10000
#define VBAT_MULTIPLIER ((RESISTOR_BAT + RESISTOR_GND) / RESISTOR_GND) / 1024.0

#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
// esp32 feather
#define VBATPIN A13
// Multiply by 1.1V, the adC reference voltage,  convert to voltage 4098 is max
// value
#define VBAT_MULTIPLIER 2.0 * 3.3 * 1.1 / 4098.0

#elif defined(ARDUINO_STM32_FEATHER)
// wiced feather
#define VBATPIN PA1
#define VBAT_MULTIPLIER 2.0 * 0.80566F / 1000.0

#elif defined(ARDUINO_FEATHER52) || defined(NRF52840_XXAA)
#define VBATPIN PIN_VBAT
#define VBAT_MV_PER_LSB                                                        \
  (0.73242188F) // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096

#ifdef NRF52840_XXAA           // if this is for nrf52840
#define VBAT_DIVIDER (0.5F)    // 150K + 150K voltage divider on VBAT
#define VBAT_MULTIPLIER (2.0F) // Compensation factor for the VBAT divider
#else
#define VBAT_DIVIDER                                                           \
  (0.71275837F) // 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
#define VBAT_MULTIPLIER (1.403F) // Compensation factor for the VBAT divider
#endif

#define REAL_VBAT_MV_PER_LSB (VBAT_MULTIPLIER * VBAT_MV_PER_LSB)

#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
#include "Adafruit_LC709203F.h"

#else
#warning "Board VBAT pin is not known!"
#endif

/**************************************************************************/
/*!
 @brief  Class that extends the SSD1306 to allow easy usage such as displaying
 the battery
 */
/**************************************************************************/
class Adafruit_FeatherOLED : public Adafruit_SSD1306 {
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
  Adafruit_FeatherOLED(TwoWire *wire = &Wire, int reset = -1)
      : Adafruit_SSD1306(128, 32, wire, reset) {
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

#endif /* _Adafruit_FeatherOLED_H_ */
