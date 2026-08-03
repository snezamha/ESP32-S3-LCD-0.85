#include "System.h"

#include "../config/Colors.h"

void System::begin()
{
    display.begin();
    drawDashboard();
}

void System::update()
{
}

void System::drawDashboard()
{
    display.clear();

    display.drawCenteredText("Lesson 8", 8, 2);
    display.drawCenteredText("LCD Dashboard", 32, 1);

    display.drawLine(10, 48, 118, 48, COLOR_DIVIDER);

    display.drawRect(10, 58, 108, 52, COLOR_ACCENT);
    display.drawCenteredText("Status", 66, 1);
    display.drawCenteredText("READY", 84, 2);

    display.fillCircle(106, 106, 5, COLOR_SUCCESS);
}