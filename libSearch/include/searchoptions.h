#ifndef _SEARCH_OPTIONS_H
#define _SEARCH_OPTIONS_H

#include <QStringList>
#include <QString>


struct SearchOptions
{
    QString strPath;
    QStringList listPatterns;
    QStringList listMasks;
    bool bCaseSensitive;
    bool bRecursive;
    unsigned long long stMinFileSize;
    unsigned long long stMaxFileSize;
    bool bCharsetDetect;
};

#endif
