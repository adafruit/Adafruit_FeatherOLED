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

  // get the current voltage of the battery from
  // one of the platform specific functions below
  float battery = getBatteryVoltage();

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

#if defined(ARDUINO_ARCH_SAMD) || defined(__AVR_ATmega32U4__)

  // m0 & 32u4 feathers
  #define VBATPIN A7

  float getBatteryVoltage() {

    float measuredvbat = analogRead(VBATPIN);

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage

    return measuredvbat;

  }

#elif defined(ESP8266)

  // esp8266 feather
  #define VBATPIN A0

  float getBatteryVoltage() {

    float measuredvbat = analogRead(VBATPIN);

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage

    return measuredvbat;

  }

#elif defined(ARDUINO_STM32_FEATHER)

  // wiced feather
  #define VBATPIN PA1

  float getBatteryVoltage() {

    pinMode(VBATPIN, INPUT_ANALOG);

    float measuredvbat = analogRead(VBATPIN);

    measuredvbat *= 2;         // we divided by 2, so multiply back
    measuredvbat *= 0.80566F;  // multiply by mV per LSB
    measuredvbat /= 1000;      // convert to voltage

    return measuredvbat;

  }

#else

  // unknown platform
  float getBatteryVoltage() {
    Serial.println("warning: unknown feather. getting battery voltage failed.");
    return 0.0F;
  }

#endif
