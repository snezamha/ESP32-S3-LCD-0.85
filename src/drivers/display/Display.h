/* #pragma once

class Display
{
public:
    void begin();

    void clear();

    void print(const char *text);
}; */
#pragma once

#include <Arduino_GFX_Library.h>

class Display
{
public:
    Display();

    void begin();
    void clear();
    void print(const char *text);

private:
    Arduino_DataBus *bus;
    Arduino_GFX *gfx;
};