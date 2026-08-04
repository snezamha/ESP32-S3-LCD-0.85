#include "ScreenManager.h"

#include <Arduino.h>

ScreenManager::ScreenManager(Display &display) : display(display)
{
}

void ScreenManager::begin(int batteryPercent, int counter)
{
    redraw(batteryPercent, counter);
}

void ScreenManager::update(int batteryPercent, int counter)
{
    unsigned long now = millis();

    if (currentId == ScreenId::Home && (now - lastHomeRefresh) >= 1000UL)
    {
        lastHomeRefresh = now;
        redraw(batteryPercent, counter);
    }
}

void ScreenManager::onMinus(int batteryPercent, int &counter)
{
    if (editingCounter)
    {
        counter--;
    }
    else
    {
        previousScreen();
    }

    redraw(batteryPercent, counter);
}

void ScreenManager::onPlus(int batteryPercent, int &counter)
{
    if (editingCounter)
    {
        counter++;
    }
    else
    {
        nextScreen();
    }

    redraw(batteryPercent, counter);
}

void ScreenManager::onSelect(int batteryPercent, int counter)
{
    if (currentId == ScreenId::Counter)
    {
        editingCounter = !editingCounter;
        redraw(batteryPercent, counter);
    }
}

void ScreenManager::onBatteryChanged(int batteryPercent, int counter)
{
    if (currentId == ScreenId::Home)
    {
        redraw(batteryPercent, counter);
    }
}

void ScreenManager::redraw(int batteryPercent, int counter)
{
    currentScreen().draw(display, batteryPercent, counter, editingCounter);
}

bool ScreenManager::isEditingCounter() const
{
    return currentId == ScreenId::Counter && editingCounter;
}

void ScreenManager::previousScreen()
{
    int id = static_cast<int>(currentId) - 1;
    if (id < 0)
    {
        id = static_cast<int>(ScreenId::Count) - 1;
    }

    currentId = static_cast<ScreenId>(id);
}

void ScreenManager::nextScreen()
{
    int id = static_cast<int>(currentId) + 1;
    if (id >= static_cast<int>(ScreenId::Count))
    {
        id = 0;
    }

    currentId = static_cast<ScreenId>(id);
}

Screen &ScreenManager::currentScreen()
{
    switch (currentId)
    {
    case ScreenId::Counter:
        return counterScreen;
    case ScreenId::Settings:
        return settingsScreen;
    case ScreenId::Home:
    default:
        return homeScreen;
    }
}
