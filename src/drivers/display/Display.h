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

    void drawBootScreen();

    int width();

    int height();

private:
    Arduino_DataBus *bus;
    Arduino_GFX *gfx;
};