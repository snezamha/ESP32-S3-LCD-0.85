#include "System.h"

#include "../config/Colors.h"
#include "../config/Pins.h"

void System::begin()
{
    keepBatteryPowerOn();

    pinMode(BUTTON_MINUS, INPUT_PULLUP);
    pinMode(BUTTON_POWER, INPUT_PULLUP);
    pinMode(BUTTON_PLUS, INPUT_PULLUP);

    analogReadResolution(12);

    display.begin();
    display.drawBootScreen();
    delay(BOOT_SCREEN_MS);

    updateBattery(true);
    screenManager.begin(batteryPercent, counter);
}

void System::update()
{
    handleButtons();
    updateBattery();
    screenManager.update(batteryPercent, counter);
}

void System::keepBatteryPowerOn()
{
    pinMode(BATTERY_ENABLE, OUTPUT);
    digitalWrite(BATTERY_ENABLE, HIGH);
    delay(50);
}

void System::powerOff()
{
    display.clear();
    display.setBacklight(false);
    delay(100);

    digitalWrite(BATTERY_ENABLE, LOW);

    while (true)
    {
        delay(1000);
    }
}

void System::handleButtons()
{
    handleButton(minusButton, &System::onMinusClick, &System::onMinusLongPress);
    handleButton(powerButton, &System::onPowerClick, &System::onPowerLongPress);
    handleButton(plusButton, &System::onPlusClick, &System::onPlusLongPress);
}

void System::handleButton(ButtonState &button, void (System::*onClick)(), void (System::*onLongPress)())
{
    bool reading = digitalRead(button.pin);
    unsigned long now = millis();

    if (reading != button.lastReading)
    {
        button.lastDebounceTime = now;
    }

    if ((now - button.lastDebounceTime) > DEBOUNCE_DELAY_MS)
    {
        if (reading != button.stableState)
        {
            button.stableState = reading;

            if (button.stableState == LOW)
            {
                button.pressedTime = now;
                button.longPressHandled = false;
            }
            else if (!button.longPressHandled)
            {
                (this->*onClick)();
            }
        }

        if (button.stableState == LOW &&
            !button.longPressHandled &&
            (now - button.pressedTime) >= LONG_PRESS_DELAY_MS)
        {
            button.longPressHandled = true;
            (this->*onLongPress)();
        }
    }

    button.lastReading = reading;
}

void System::onMinusClick()
{
    screenManager.onMinus(batteryPercent, counter);
}

void System::onMinusLongPress()
{
    if (screenManager.isEditingCounter())
    {
        counter = 0;
        screenManager.redraw(batteryPercent, counter);
    }
}

void System::onPowerClick()
{
    screenManager.onSelect(batteryPercent, counter);
}

void System::onPowerLongPress()
{
    powerOff();
}

void System::onPlusClick()
{
    screenManager.onPlus(batteryPercent, counter);
}

void System::onPlusLongPress()
{
    if (screenManager.isEditingCounter())
    {
        counter += 5;
        screenManager.redraw(batteryPercent, counter);
    }
}

void System::updateBattery(bool force)
{
    unsigned long now = millis();

    if (!force && (now - lastBatteryRefresh) < BATTERY_REFRESH_MS)
    {
        return;
    }

    lastBatteryRefresh = now;
    int nextPercent = readBatteryPercent();

    if (force || nextPercent != batteryPercent)
    {
        batteryPercent = nextPercent;
        screenManager.onBatteryChanged(batteryPercent, counter);
    }
}

float System::readBatteryVoltage() const
{
    int raw = analogRead(BATTERY_ADC);
    float adcVoltage = (raw * ADC_REFERENCE_VOLTAGE) / ADC_MAX_READING;
    return adcVoltage * BATTERY_DIVIDER_RATIO;
}

int System::readBatteryPercent() const
{
    float voltage = readBatteryVoltage();
    float percent = ((voltage - BATTERY_EMPTY_VOLTAGE) * 100.0F) /
                    (BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE);

    return constrain(static_cast<int>(percent + 0.5F), 0, 100);
}
