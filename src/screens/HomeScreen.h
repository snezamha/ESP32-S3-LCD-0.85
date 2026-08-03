#pragma once

#include "../drivers/display/Display.h"

class HomeScreen
{
public:
    HomeScreen(Display &display);

    void begin();

    void update();

    void draw();

private:
    Display &display;

    uint8_t hour;
    uint8_t minute;

    const char *day;
    const char *date;
};