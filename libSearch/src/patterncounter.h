#ifndef PATTERNCOUNTER_H
#define PATTERNCOUNTER_H

#include "multipatternsearcher.h"

#include <QString>

class CPatternCounter
{
    MultiPatternSearcher& m_searcher;
    bool m_bCaseSensitive;
    int m_nOverlap;
    PatternMatchContainer m_foundPatterns;
    QString m_strPreBlock;
public:
    CPatternCounter( MultiPatternSearcher& searcher, bool bCaseSensitive, int nOverlap );
    bool OnChunk( const QString& strChunk );
    bool MatchedOk();
    bool SomePatterns();
};

#endif
