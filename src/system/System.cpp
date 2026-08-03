#include "System.h"

void System::begin()
{
    display.begin();

    homeScreen.begin();
    homeScreen.draw();
}

void System::update()
{
    homeScreen.update();
}