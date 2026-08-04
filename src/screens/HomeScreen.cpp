#include "HomeScreen.h"

#include <Arduino.h>

#include "../config/Colors.h"

void HomeScreen::draw(Display &display, int batteryPercent, int, bool)
{
    char batteryText[20];
    char uptimeText[24];

    snprintf(batteryText, sizeof(batteryText), "Battery: %d%%", batteryPercent);
    snprintf(uptimeText, sizeof(uptimeText), "Uptime: %lus", millis() / 1000UL);

    display.clear();
    display.drawCenteredText("HOME", 8, 2);
    display.drawLine(16, 30, 112, 30, COLOR_DIVIDER);
    display.drawCenteredText(batteryText, 43, 1);
    display.drawCenteredText(uptimeText, 59, 1);
    display.drawCenteredText("System: ready", 75, 1);
    display.fillCircle(64, 96, 5, COLOR_SUCCESS);
    display.drawCenteredText("-  pages  +", 112, 1);
}
