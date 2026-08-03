#pragma once

#include <Arduino.h>

#include "../drivers/display/Display.h"

class System
{
public:
    void begin();
    void update();

private:
    static constexpr unsigned long DEBOUNCE_DELAY_MS = 40;
    static constexpr unsigned long LONG_PRESS_DELAY_MS = 800;

    void handleButton();
    void drawDashboard();
    void drawCounter();

    Display display;

    int counter = 0;
    bool buttonStableState = HIGH;
    bool lastButtonReading = HIGH;
    bool longPressHandled = false;
    unsigned long lastDebounceTime = 0;
    unsigned long buttonPressedTime = 0;
};