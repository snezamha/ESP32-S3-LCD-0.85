#pragma once

#include "../drivers/display/Display.h"
#include "../screens/HomeScreen.h"

class System
{
public:
    void begin();
    void update();

private:
    Display display;
    HomeScreen homeScreen{display};
};