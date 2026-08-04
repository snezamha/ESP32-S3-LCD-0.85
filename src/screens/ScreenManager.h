#pragma once

#include "CounterScreen.h"
#include "HomeScreen.h"
#include "SettingsScreen.h"

enum class ScreenId : uint8_t
{
    Home,
    Counter,
    Settings,
    Count
};

class ScreenManager
{
public:
    explicit ScreenManager(Display &display);

    void begin(int batteryPercent, int counter);
    void update(int batteryPercent, int counter);
    void onMinus(int batteryPercent, int &counter);
    void onPlus(int batteryPercent, int &counter);
    void onSelect(int batteryPercent, int counter);
    void onBatteryChanged(int batteryPercent, int counter);
    void redraw(int batteryPercent, int counter);

    bool isEditingCounter() const;

private:
    void previousScreen();
    void nextScreen();
    Screen &currentScreen();

    Display &display;
    HomeScreen homeScreen;
    CounterScreen counterScreen;
    SettingsScreen settingsScreen;
    ScreenId currentId = ScreenId::Home;
    bool editingCounter = false;
    unsigned long lastHomeRefresh = 0;
};
