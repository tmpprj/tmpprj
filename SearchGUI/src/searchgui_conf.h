#ifndef _SEARCHGUI_PARAMS_H_
#define _SEARCHGUI_PARAMS_H_

#include <QtCore>

namespace SearchGUI
{
    struct Params
    {
        QMap< QString, QVariant > extensions;
        QStringList searchPaths;
        QStringList searches;

        Params();
        ~Params();
    };

    Params& Conf();
}

#endif

