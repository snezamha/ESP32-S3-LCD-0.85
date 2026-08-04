#pragma once

#include "Screen.h"

class HomeScreen : public Screen
{
public:
    void draw(Display &display, int batteryPercent, int counter, bool editing) override;
};
