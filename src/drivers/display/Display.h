#pragma once

#include <Arduino_GFX_Library.h>

class Display
{
public:
    Display();

    void begin();

    void clear();

    void print(const char *text);

    void printCentered(const char *text, int y);

    void drawBootScreen();

private:
    Arduino_DataBus *bus;
    Arduino_GFX *gfx;
};