#ifndef LIBSEARCH_COMMON_H
#define LIBSEARCH_COMMON_H

#include <QStringList>
#include "multipatternsearcher.h"

void ConvertListToPatterns( const QStringList& listPatterns, bool bCaseSensitive, PatternsContainer& patterns );

#endif
