#include "Display.h"
#include "../../config/Pins.h"

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
    gfx->setTextColor(RGB565_WHITE);
    gfx->setTextSize(2);

    gfx->println("ESP32-S3-LCD-0.85");
    gfx->println();
    gfx->println("Framework");
    gfx->println("v0.1.0");
}

void Display::clear()
{
    gfx->fillScreen(RGB565_BLACK);
}

void Display::print(const char *text)
{
    gfx->println(text);
}