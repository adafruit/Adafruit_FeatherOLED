/**************************************************************************/
/*!
 * @file     Adafruit_FeatherOLED_WiFi.cpp
 * @author   ktown
 */
/**************************************************************************/
#include "Adafruit_FeatherOLED_WiFi.h"

/**************************************************************************/
/*!
 * @brief  Converts RSSI from dBm to quality percentage
 */
/**************************************************************************/
int Adafruit_FeatherOLED_WiFi::rssiToQualityPercentage(void) {
  int quality;
  if (_rssi <= -100) {
    quality = 0;
  } else if (_rssi >= -50) {
    quality = 100;
  } else {
    quality = 2 * (_rssi + 100);
  }

  return quality;
}

/******************************************************************************/
/*!
    @brief  Renders the RSSI icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderRSSI(void) {
  if (_rssiVisible) {
    setCursor(0, 0);

    if (_connected) {
      renderRSSIIcon();

      if (_rssiAsPercentage) {
        int quality = rssiToQualityPercentage();
        if (quality == 0) {
          print("---");
        } else {
          char buf[5];
          itoa(quality, buf, 10);
          strcat(buf, "%");
          print(buf);
        }
      } else {
        print(_rssi);
        print(" dBm");
      }
    } else {
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
void Adafruit_FeatherOLED_WiFi::renderRSSIIcon(void) {
  if (_rssiIcon) {
    int quality = rssiToQualityPercentage();
    if (quality == 0) {
      print("---");
    } else {
      // Render the first bar if there is any signal at all
      fillRect(RSSIICON_STARTX, RSSIICON_STARTY, RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT, WHITE);
    }

    // Render the second bar
    if (quality >= 45) {
      fillRect(RSSIICON_STARTX + 3, RSSIICON_STARTY - 1, RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT + 1, WHITE);
    }

    // Render the third bar
    if (quality >= 70) {
      fillRect(RSSIICON_STARTX + 6, RSSIICON_STARTY - 2, RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT + 2, WHITE);
    }

    // Render the fourth bar. The most coveted of all bars.
    if (quality >= 90) {
      fillRect(RSSIICON_STARTX + 9, RSSIICON_STARTY - 4, RSSIICON_BARWIDTH,
               RSSIICON_STARTHEIGHT + 4, WHITE);
    }

    setCursor(RSSITEXT_STARTX, RSSITEXT_STARTY);
  } else {
    print("RSSI:");
  }
}

/******************************************************************************/
/*!
    @brief  Renders the connection status icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderConnected(void) {
  if (_connectedVisible) {
    setCursor(100, 24);
    if (_connected) {
      println("CONN");
    } else {
      println("----");
    }
  }
}

/******************************************************************************/
/*!
    @brief  Renders the connection status icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_WiFi::renderIPAddress(void) {
  if (_ipAddressVisible) {
    if (_connected) {
      setCursor(0, 24);
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
void Adafruit_FeatherOLED_WiFi::refreshIcons(void) {
  fillRect(0, 0, 128, 8, BLACK);
  if (_ipAddressVisible) {
    fillRect(0, 24, 128, 8, BLACK);
    renderIPAddress();
  }
  renderBattery();
  renderRSSI();
  renderConnected();
  display();
}
