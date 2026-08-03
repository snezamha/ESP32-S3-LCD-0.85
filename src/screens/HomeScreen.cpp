#include "HomeScreen.h"

#include "../config/Colors.h"

#include <stdio.h>

HomeScreen::HomeScreen(Display &display)
    : display(display)
{
}

void HomeScreen::begin()
{
    hour = 12;
    minute = 45;

    day = "Tuesday";
    date = "04 Aug 2026";
}

void HomeScreen::update()
{
}

void HomeScreen::draw()
{
    display.clear();

    char buffer[6];
    sprintf(buffer, "%02d:%02d", hour, minute);

    display.setTextColor(COLOR_TEXT);

    // Time
    display.drawCenteredText(buffer, 32, 3);

    // Day
    display.drawCenteredText(day, 76, 2);

    // Date
    display.drawCenteredText(date, 102, 1);
}