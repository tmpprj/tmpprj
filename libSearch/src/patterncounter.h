#ifndef PATTERNCOUNTER_H
#define PATTERNCOUNTER_H

#include "multipatternsearcher.h"

#include <QString>

class CPatternCounter
{
    MultiPatternSearcher& m_searcher;
    bool m_bCaseSensitive;
    PatternMatchContainer m_foundPatterns;
public:
    CPatternCounter( MultiPatternSearcher& searcher, bool bCaseSensitive );
    bool OnChunk( const QString& strChunk );
    bool MatchedOk();
    bool SomePatterns();
};

#endif
