#pragma once

#include <Arduino_GFX_Library.h>

class Display
{
public:
    Display();

    void begin();

    void clear();

    void setTextSize(uint8_t size);

    void setTextColor(uint16_t color);

    void drawText(const char *text);

    void drawCenteredText(
        const char *text,
        int y,
        uint8_t textSize = 1);

    // Graphics API
    void drawPixel(
        int16_t x,
        int16_t y,
        uint16_t color);

    void drawLine(
        int16_t x0,
        int16_t y0,
        int16_t x1,
        int16_t y1,
        uint16_t color);

    void drawRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t color);

    void fillRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t color);

    void drawCircle(
        int16_t x,
        int16_t y,
        int16_t r,
        uint16_t color);

    void fillCircle(
        int16_t x,
        int16_t y,
        int16_t r,
        uint16_t color);

    void drawBootScreen();

    int width();

    int height();

private:
    Arduino_DataBus *bus;
    Arduino_GFX *gfx;
};