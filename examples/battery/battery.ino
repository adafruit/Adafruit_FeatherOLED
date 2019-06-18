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

#if defined(ARDUINO_ARCH_SAMD)
  // m0 and m4 feathers
  #define VBATPIN A7

  float getBatteryVoltage() {

    float measuredvbat = analogRead(VBATPIN);

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage

    return measuredvbat;

  }

#elif defined(__AVR_ATmega32U4__)

  // 32u4 feather
  #define VBATPIN A9

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

  /*
   * The ESP8266 Feather Huzzah does not have an internal voltage divider, so you must build one.
   * However, the voltage on the Analog Input must be between 0-1.0V or you could risk damaging
   * the chip. So please keep this in mind when selecting resistor values. For the default values
   * you could use a 100K resistor between ADC and USB (R1) and a 10K Resistor between ADC and Ground (R2) 
   * to use these values.
   */

  float getBatteryVoltage() {

    float measuredvbat = analogRead(VBATPIN);

    int R1 = 100000;
    int R2 = 10000;

    measuredvbat *= (R1 / R2); // we divided by 10, so multiply back
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

#elif defined(ARDUINO_FEATHER52)

  #define VBATPIN PIN_VBAT
  #define VBAT_MV_PER_LSB   (0.73242188F)   // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
  
  #ifdef NRF52840_XXAA    // if this is for nrf52840
  #define VBAT_DIVIDER      (0.5F)          // 150K + 150K voltage divider on VBAT
  #define VBAT_DIVIDER_COMP (2.0F)          // Compensation factor for the VBAT divider
  #else
  #define VBAT_DIVIDER      (0.71275837F)   // 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
  #define VBAT_DIVIDER_COMP (1.403F)        // Compensation factor for the VBAT divider
  #endif

  #define REAL_VBAT_MV_PER_LSB (VBAT_DIVIDER_COMP * VBAT_MV_PER_LSB)
  
  float getBatteryVoltage() {
    int raw;
    
    // Set the analog reference to 3.0V (default = 3.6V)
    analogReference(AR_INTERNAL_3_0);
    
    // Set the resolution to 12-bit (0..4095)
    analogReadResolution(12); // Can be 8, 10, 12 or 14
    
    // Let the ADC settle
    delay(1);
    
    // Get the raw 12-bit, 0..3000mV ADC value
    raw = analogRead(VBATPIN);
    
    // Set the ADC back to the default settings
    analogReference(AR_DEFAULT);
    analogReadResolution(10);
    
    // Convert the raw value to compensated mv, taking the resistor-
    // divider into account (providing the actual LIPO voltage)
    // ADC range is 0..3000mV and resolution is 12-bit (0..4095),
    return ((float)raw * REAL_VBAT_MV_PER_LSB) / 1000.0;
  }
 
#else

  // unknown platform
  float getBatteryVoltage() {
    Serial.println("warning: unknown feather. getting battery voltage failed.");
    return 0.0F;
  }

#endif
