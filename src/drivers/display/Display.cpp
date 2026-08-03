#include "Display.h"
#include "../../config/Pins.h"
#include "../../config/Version.h"
#include "../../config/Colors.h"

Display::Display()
{
    bus = new Arduino_ESP32SPI(
        LCD_DC,
        LCD_CS,
        LCD_SCK,
        LCD_MOSI);

    gfx = new Arduino_GC9107(
        bus,
        LCD_RST,
        0,
        true);
}

void Display::begin()
{
    if (!gfx->begin())
    {
        return;
    }

    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);

    clear();

    gfx->setCursor(10, 20);
    gfx->setTextColor(COLOR_TEXT);
    gfx->setTextSize(2);

    gfx->println(FRAMEWORK_NAME);
    gfx->println();
    gfx->println(FRAMEWORK_VERSION);
}

void Display::clear()
{
    gfx->fillScreen(COLOR_BACKGROUND);
}

void Display::print(const char *text)
{
    gfx->println(text);
}