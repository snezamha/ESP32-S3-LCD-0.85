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
}

void Display::drawBootScreen()
{
    clear();

    gfx->setTextColor(COLOR_TEXT);

    gfx->setTextSize(2);
    drawCenteredText("ESP32", 20);
    drawCenteredText("Framework", 45);

    gfx->setTextSize(1);
    drawCenteredText(FRAMEWORK_VERSION, 80);
}

void Display::clear()
{
    gfx->fillScreen(COLOR_BACKGROUND);
}

void Display::setTextSize(uint8_t size)
{
    gfx->setTextSize(size);
}

void Display::setTextColor(uint16_t color)
{
    gfx->setTextColor(color);
}

void Display::drawText(const char *text)
{
    gfx->println(text);
}

void Display::drawCenteredText(const char *text, int y, uint8_t textSize)
{
    gfx->setTextSize(textSize);

    int16_t x1, y1;
    uint16_t w, h;

    gfx->getTextBounds(text, 0, y, &x1, &y1, &w, &h);

    int x = (gfx->width() - w) / 2;
    gfx->setCursor(x, y);
    gfx->print(text);
}

void Display::drawPixel(
    int16_t x,
    int16_t y,
    uint16_t color)
{
    gfx->drawPixel(x, y, color);
}

void Display::drawLine(
    int16_t x0,
    int16_t y0,
    int16_t x1,
    int16_t y1,
    uint16_t color)
{
    gfx->drawLine(x0, y0, x1, y1, color);
}

void Display::drawRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color)
{
    gfx->drawRect(x, y, w, h, color);
}

void Display::fillRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color)
{
    gfx->fillRect(x, y, w, h, color);
}

void Display::drawCircle(
    int16_t x,
    int16_t y,
    int16_t r,
    uint16_t color)
{
    gfx->drawCircle(x, y, r, color);
}

void Display::fillCircle(
    int16_t x,
    int16_t y,
    int16_t r,
    uint16_t color)
{
    gfx->fillCircle(x, y, r, color);
}

int Display::width()
{
    return gfx->width();
}

int Display::height()
{
    return gfx->height();
}