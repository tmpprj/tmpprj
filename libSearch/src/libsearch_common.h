#ifndef LIBSEARCH_COMMON_H
#define LIBSEARCH_COMMON_H

#include <QStringList>
#include "multipatternsearcher.h"

QByteArray StringToCommon( const QString& str, bool bCaseSensitive, bool bRaw = false );
void ConvertListToPatterns( const QStringList& listPatterns, bool bCaseSensitive, bool bRaw, PatternsContainer& patterns );

#endif
