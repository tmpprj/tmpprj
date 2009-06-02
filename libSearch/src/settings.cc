#include "settings.h"

QSettings& Settings()
{
    static QSettings settings( "settings.ini", QSettings::IniFormat );

    return settings;
}

