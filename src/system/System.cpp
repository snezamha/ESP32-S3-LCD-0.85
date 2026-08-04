#include "System.h"

#include "../config/Colors.h"
#include "../config/Pins.h"

void System::begin()
{
    pinMode(BUTTON_BOOT, INPUT_PULLUP);
    pinMode(BUTTON_POWER, INPUT_PULLUP);
    pinMode(BUTTON_PLUS, INPUT_PULLUP);
    pinMode(LCD_BL, OUTPUT);

    analogReadResolution(12);

    display.begin();
    updateBattery(true);
    drawDashboard();
}

void System::update()
{
    handleButtons();

    if (displayOn)
    {
        updateBattery();
    }
}

void System::handleButtons()
{
    handleButton(bootButton, &System::onBootClick, &System::onBootLongPress);
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

void System::onBootClick()
{
    if (!displayOn)
    {
        return;
    }

    counter++;
    drawCounter();
}

void System::onBootLongPress()
{
    if (!displayOn)
    {
        return;
    }

    counter = 0;
    drawCounter();
}

void System::onPowerClick()
{
    setDisplayOn(!displayOn);
}

void System::onPowerLongPress()
{
    setDisplayOn(!displayOn);
}

void System::onPlusClick()
{
    if (!displayOn)
    {
        return;
    }

    counter += 5;
    drawCounter();
}

void System::onPlusLongPress()
{
    if (!displayOn)
    {
        return;
    }

    updateBattery(true);
}

void System::setDisplayOn(bool on)
{
    if (displayOn == on)
    {
        return;
    }

    displayOn = on;

    if (displayOn)
    {
        digitalWrite(LCD_BL, HIGH);
        updateBattery(true);
        drawDashboard();
    }
    else
    {
        display.clear();
        digitalWrite(LCD_BL, LOW);
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
        drawBattery();
    }
}

float System::readBatteryVoltage()
{
    int raw = analogRead(BATTERY_ADC);
    float adcVoltage = (raw * ADC_REFERENCE_VOLTAGE) / ADC_MAX_READING;
    return adcVoltage * BATTERY_DIVIDER_RATIO;
}

int System::readBatteryPercent()
{
    float voltage = readBatteryVoltage();
    float percent = ((voltage - BATTERY_EMPTY_VOLTAGE) * 100.0F) /
                    (BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE);

    return constrain(static_cast<int>(percent + 0.5F), 0, 100);
}

void System::drawDashboard()
{
    if (!displayOn)
    {
        return;
    }

    display.clear();

    display.drawCenteredText("Lesson 10", 8, 2);
    display.drawCenteredText("PWR toggles display", 30, 1);
    drawBattery();

    display.drawLine(16, 52, 112, 52, COLOR_DIVIDER);

    display.drawCenteredText("BOOT +1", 62, 1);
    display.drawCenteredText("PLUS +5", 76, 1);
    drawCounter();

    display.fillCircle(112, 112, 4, COLOR_SUCCESS);
}

void System::drawCounter()
{
    if (!displayOn)
    {
        return;
    }

    char text[12];
    snprintf(text, sizeof(text), "%d", counter);

    display.fillRect(34, 90, 60, 22, COLOR_BACKGROUND);
    display.drawCenteredText(text, 92, 2);
}

void System::drawBattery()
{
    if (!displayOn)
    {
        return;
    }

    char text[16];
    snprintf(text, sizeof(text), "Battery: %d%%", batteryPercent);

    display.fillRect(12, 42, 104, 8, COLOR_BACKGROUND);
    display.drawCenteredText(text, 42, 1);
}