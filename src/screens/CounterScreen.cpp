#include "CounterScreen.h"

#include <Arduino.h>

#include "../config/Colors.h"

void CounterScreen::draw(Display &display, int, int counter, bool editing)
{
    char counterText[16];
    snprintf(counterText, sizeof(counterText), "%d", counter);

    display.clear();
    display.drawCenteredText("COUNTER", 8, 2);
    display.drawLine(16, 30, 112, 30, COLOR_DIVIDER);
    display.drawCenteredText(counterText, 47, 4);

    if (editing)
    {
        display.drawRect(20, 40, 88, 43, COLOR_ACCENT);
        display.drawCenteredText("- change +", 92, 1);
        display.drawCenteredText("PWR: done", 108, 1);
    }
    else
    {
        display.drawCenteredText("PWR: edit", 92, 1);
        display.drawCenteredText("-  pages  +", 108, 1);
    }
}
