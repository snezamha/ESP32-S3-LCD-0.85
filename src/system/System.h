#pragma once

#include "../drivers/display/Display.h"

class System
{
public:
    void begin();
    void update();

private:
    void drawDashboard();

    Display display;
};