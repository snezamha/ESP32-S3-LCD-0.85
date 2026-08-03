#pragma once

#include "../drivers/display/Display.h"

class System
{
public:
    void begin();
    void update();

private:
    Display display;
};