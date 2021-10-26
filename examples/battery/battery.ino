// Adafruit OLED FeatherWing Battery Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>

Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();

// integer variable to hold current counter value
int count = 0;

void setup()
{
  Serial.begin(115200);
  oled.init();
  oled.setBatteryVisible(true);
}

void loop()
{

  // clear the current count
  oled.clearDisplay();

  // get the current voltage of the battery
  float battery = oled.getBatteryVoltage();

  // update the battery icon
  oled.setBattery(battery);
  oled.renderBattery();

  // print the count value to the OLED
  oled.print("count: ");
  oled.println(count);

  // update the display with the new count
  oled.display();

  // increment the counter by 1
  count++;

  // delay 1 second (1 second == 1000 milliseconds)
  delay(1000);

}
