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

        Params();
    };

    Params& Conf();
}

#endif

