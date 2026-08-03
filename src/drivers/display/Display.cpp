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

    drawBootScreen();
}

void Display::drawBootScreen()
{
    clear();

    gfx->setTextColor(COLOR_TEXT);

    gfx->setTextSize(2);
    printCentered("ESP32", 20);

    printCentered("Framework", 45);

    gfx->setTextSize(1);
    printCentered(FRAMEWORK_VERSION, 80);
}

void Display::clear()
{
    gfx->fillScreen(COLOR_BACKGROUND);
}

void Display::print(const char *text)
{
    gfx->println(text);
}

void Display::printCentered(const char *text, int y)
{
    int16_t x1, y1;
    uint16_t w, h;

    gfx->getTextBounds(text, 0, y, &x1, &y1, &w, &h);

    int x = (gfx->width() - w) / 2;

    gfx->setCursor(x, y);

    gfx->print(text);
}