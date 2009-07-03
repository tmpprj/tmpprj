#ifndef PATTERNCOUNTER_H
#define PATTERNCOUNTER_H

#include "multipatternsearcher.h"

#include <QString>

class CPatternCounter
{
    MultiPatternSearcher& m_searcher;
    PatternMatchContainer m_foundPatterns;
public:
    CPatternCounter( MultiPatternSearcher& searcher );
    bool OnChunk( const QString& strChunk );
    bool MatchedOk();
};

#endif
