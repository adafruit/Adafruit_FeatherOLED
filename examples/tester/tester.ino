#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>

Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();

void setup()
{
  oled.init();
  oled.writeMessage("192.168.0.1");
  oled.refresh();
}

void loop()
{

}
