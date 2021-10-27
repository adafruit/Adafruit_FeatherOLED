/*!
 * @file     Adafruit_FeatherOLED_WiFi.h
 */

#ifndef _Adafruit_FeatherOLED_WiFi_H_
/*!
 @brief Adafruit FeatherOLED WiFi H
 */
#define _Adafruit_FeatherOLED_WiFi_H_

#include <Adafruit_FeatherOLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

/**************************************************************************/
/*!
 @brief  Class that extends Adafruit_FeatherOLED to help with some WiFi related
 helper functions
 */
/**************************************************************************/
class Adafruit_FeatherOLED_WiFi : public Adafruit_FeatherOLED {
private:
  int rssiToQualityPercentage(void);

protected:
  bool _connected; /*!<  Are we connected? */         //
  bool _connectedVisible; /*!<  Show connectivity */  //
  int _rssi; /*!<  RSSI Value */                      //
  bool _rssiIcon; /*!<  RSSI as Icon */               //
  bool _rssiAsPercentage; /*!<  RSSI as Percentage */ //
  bool _rssiVisible; /*!<  Display RSSI */            //
  int32_t _ipAddress; /*!<  IP Address */             //
  bool _ipAddressVisible; /*!<  IP Address Visible */ //

  void renderRSSI(void);
  void renderRSSIIcon(void);
  void renderConnected(void);
  void renderIPAddress(void);

public:
  /**************************************************************************/
  /*!
   @brief  Class Constructor
   @param  wire The Wire object
   @param  reset Perform a Reset on initialization
   */
  /**************************************************************************/
  Adafruit_FeatherOLED_WiFi(TwoWire *wire = &Wire, int reset = -1)
      : Adafruit_FeatherOLED(wire, reset) {
    _connected = false;
    _connectedVisible = true;
    _rssi = -99;
    _rssiIcon = false;
    _rssiAsPercentage = false;
    _rssiVisible = true;
    _ipAddress = 0;
    _ipAddressVisible = true;
  }

  /**************************************************************************/
  /*!
   @brief  Sets if we're connected
   @param  conn Are we connected?
   */
  /**************************************************************************/
  void setConnected(bool conn) { _connected = conn; }

  /**************************************************************************/
  /*!
   @brief  Sets if the connection status is visible
   @param  enable Enable visibility?
   */
  /**************************************************************************/
  void setConnectedVisible(bool enable) { _connectedVisible = enable; }

  /**************************************************************************/
  /*!
   @brief  Sets the RSSI value
   @param  rssi The value
   */
  /**************************************************************************/
  void setRSSI(int rssi) { _rssi = rssi; }

  /**************************************************************************/
  /*!
   @brief  Sets if the RSSI is an Icon
   @param  enable Enable icon?
   */
  /**************************************************************************/
  void setRSSIIcon(bool enable) { _rssiIcon = enable; }

  /**************************************************************************/
  /*!
   @brief  Sets if the RSSI is a percentage or value
   @param  enable Is it a percentage?
   */
  /**************************************************************************/
  void setRSSIAsPercentage(bool enable) { _rssiAsPercentage = enable; }

  /**************************************************************************/
  /*!
   @brief  Sets if the RSSI info is visible
   @param  enable Display the RSSI info?
   */
  /**************************************************************************/
  void setRSSIVisible(bool enable) { _rssiVisible = enable; }

  /**************************************************************************/
  /*!
   @brief  Sets the IP Address
   @param  addr The IP Address
   */
  /**************************************************************************/
  void setIPAddress(uint32_t addr) { _ipAddress = addr; }

  /**************************************************************************/
  /*!
   @brief  Sets the IP Address Visiblity
   @param  enable Display the IP Address?
   */
  /**************************************************************************/
  void setIPAddressVisible(bool enable) { _ipAddressVisible = enable; }

  /**************************************************************************/
  /*!
   @brief  Refresh all icons based on current settings
   */
  /**************************************************************************/
  void refreshIcons(void);
};

#define RSSITEXT_STARTX 14     ///< RSSI Text X Position
#define RSSITEXT_STARTY 0      ///< RSSI Text Y Position
#define RSSIICON_STARTX 0      ///< RSSI Icon X Position
#define RSSIICON_STARTY 4      ///< RSSI Icon Y Position
#define RSSIICON_STARTHEIGHT 3 ///< RSSI Icon Height
#define RSSIICON_BARWIDTH 2    ///< RSSI Icon Width

#endif /* _Adafruit_FeatherOLED_WiFi_H_ */
