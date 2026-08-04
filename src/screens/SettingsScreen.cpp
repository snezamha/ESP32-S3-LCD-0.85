#include "SettingsScreen.h"

#include "../config/Colors.h"
#include "../config/Version.h"

void SettingsScreen::draw(Display &display, int, int, bool)
{
    char versionText[20];
    snprintf(versionText, sizeof(versionText), "Version: %s", FRAMEWORK_VERSION);

    display.clear();
    display.drawCenteredText("SETTINGS", 8, 2);
    display.drawLine(16, 30, 112, 30, COLOR_DIVIDER);
    display.drawCenteredText("Brightness: 100%", 43, 1);
    display.drawCenteredText("Screen timeout: off", 59, 1);
    display.drawCenteredText(versionText, 75, 1);
    display.drawCenteredText("Next: PWM", 92, 1);
    display.drawCenteredText("-  pages  +", 112, 1);
}
