#pragma once

#include <Arduino.h>

#include "../config/Pins.h"
#include "../drivers/display/Display.h"
#include "../screens/ScreenManager.h"

class System
{
public:
    void begin();
    void update();

private:
    static constexpr unsigned long BOOT_SCREEN_MS = 1200;
    static constexpr unsigned long DEBOUNCE_DELAY_MS = 40;
    static constexpr unsigned long LONG_PRESS_DELAY_MS = 1200;
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

    void keepBatteryPowerOn();
    void powerOff();

    void handleButtons();
    void handleButton(ButtonState &button, void (System::*onClick)(), void (System::*onLongPress)());

    void onMinusClick();
    void onMinusLongPress();
    void onPowerClick();
    void onPowerLongPress();
    void onPlusClick();
    void onPlusLongPress();

    void updateBattery(bool force = false);
    float readBatteryVoltage() const;
    int readBatteryPercent() const;

    Display display;
    ScreenManager screenManager{display};

    int counter = 0;
    int batteryPercent = 0;
    unsigned long lastBatteryRefresh = 0;

    ButtonState minusButton{BUTTON_MINUS};
    ButtonState powerButton{BUTTON_POWER};
    ButtonState plusButton{BUTTON_PLUS};
};
