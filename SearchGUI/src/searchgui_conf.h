#ifndef _SEARCHGUI_PARAMS_H_
#define _SEARCHGUI_PARAMS_H_

#include <QtCore>
#include <settings.h>

namespace SearchGUI
{
    struct Params
    {
        ConfParam< QMap< QString, QVariant > > mapExtensions;
        ConfParam< bool > bCaseSensitive;
        ConfParam< bool > bRecursive;
        ConfParam< QStringList > listMasks;
        ConfParam< QStringList > listSearches;
        ConfParam< QStringList > listSearchPaths;
        ConfParam< bool > bFileSizeLimits;
        ConfParam< unsigned long long > ullMinFileSize;
        ConfParam< unsigned long long > ullMaxFileSize;
        ConfParam< bool > bCharsetDetect;


        Params();
    };

    Params& Conf();
}

#endif

