#include "System.h"

#include "../config/Colors.h"
#include "../config/Pins.h"

void System::begin()
{
    pinMode(BUTTON_BOOT, INPUT_PULLUP);

    display.begin();
    drawDashboard();
}

void System::update()
{
    handleButton();
}

void System::handleButton()
{
    bool reading = digitalRead(BUTTON_BOOT);
    unsigned long now = millis();

    if (reading != lastButtonReading)
    {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > DEBOUNCE_DELAY_MS)
    {
        if (reading != buttonStableState)
        {
            buttonStableState = reading;

            if (buttonStableState == LOW)
            {
                buttonPressedTime = now;
                longPressHandled = false;
            }
            else if (!longPressHandled)
            {
                counter++;
                drawCounter();
            }
        }

        if (buttonStableState == LOW &&
            !longPressHandled &&
            (now - buttonPressedTime) >= LONG_PRESS_DELAY_MS)
        {
            counter = 0;
            longPressHandled = true;
            drawCounter();
        }
    }

    lastButtonReading = reading;
}

void System::drawDashboard()
{
    display.clear();

    display.drawCenteredText("Lesson 9", 8, 2);
    display.drawCenteredText("Button Events", 32, 1);

    display.drawLine(10, 48, 118, 48, COLOR_DIVIDER);

    display.drawRect(10, 58, 108, 52, COLOR_ACCENT);
    display.drawCenteredText("BOOT count", 66, 1);
    drawCounter();

    display.fillCircle(106, 106, 5, COLOR_SUCCESS);
}

void System::drawCounter()
{
    char text[12];
    snprintf(text, sizeof(text), "%d", counter);

    display.fillRect(34, 80, 60, 22, COLOR_BACKGROUND);
    display.drawCenteredText(text, 84, 2);
}