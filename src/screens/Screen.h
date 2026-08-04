#pragma once

#include "../drivers/display/Display.h"

class Screen
{
public:
    virtual ~Screen() = default;
    virtual void draw(Display &display, int batteryPercent, int counter, bool editing) = 0;
};
