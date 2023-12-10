#include "startupmode.h"

StartupMode::StartupMode(QString mode) // make it so you can inialize this enum using the a string with the enumerable options for json parsing
{
    currentMode = manual;
    if(mode == "manual") currentMode = manual;
    if(mode == "atStartup") currentMode = atStartup;
    if(mode == "date") currentMode = date;

}

QString StartupMode::toString() const
{
    if(currentMode == manual) return "manual";
    if(currentMode == atStartup) return "atStartup";
    if(currentMode == date) return "date";
    return "manual";

}
