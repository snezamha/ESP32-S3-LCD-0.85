#pragma once

#include <Arduino.h>

#include "../config/Pins.h"
#include "../drivers/display/Display.h"

class System
{
public:
    void begin();
    void update();

private:
    static constexpr unsigned long DEBOUNCE_DELAY_MS = 40;
    static constexpr unsigned long LONG_PRESS_DELAY_MS = 800;
    static constexpr unsigned long BATTERY_REFRESH_MS = 2000;
    static constexpr float ADC_REFERENCE_VOLTAGE = 3.3F;
    static constexpr float ADC_MAX_READING = 4095.0F;
    static constexpr float BATTERY_DIVIDER_RATIO = 3.0F;
    static constexpr float BATTERY_EMPTY_VOLTAGE = 3.3F;
    static constexpr float BATTERY_FULL_VOLTAGE = 4.2F;

    struct ButtonState
    {
        int pin;
        bool stableState = HIGH;
        bool lastReading = HIGH;
        bool longPressHandled = false;
        unsigned long lastDebounceTime = 0;
        unsigned long pressedTime = 0;
    };

    void handleButtons();
    void handleButton(ButtonState &button, void (System::*onClick)(), void (System::*onLongPress)());
    void onBootClick();
    void onBootLongPress();
    void onPowerClick();
    void onPowerLongPress();
    void onPlusClick();
    void onPlusLongPress();
    void setDisplayOn(bool on);
    void updateBattery(bool force = false);
    float readBatteryVoltage();
    int readBatteryPercent();
    void drawDashboard();
    void drawCounter();
    void drawBattery();

    Display display;

    int counter = 0;
    int batteryPercent = 0;
    bool displayOn = true;
    unsigned long lastBatteryRefresh = 0;

    ButtonState bootButton{BUTTON_BOOT};
    ButtonState powerButton{BUTTON_POWER};
    ButtonState plusButton{BUTTON_PLUS};
};