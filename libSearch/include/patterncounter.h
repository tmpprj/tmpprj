#ifndef PATTERNCOUNTER_H
#define PATTERNCOUNTER_H

#include "multipatternsearcher.h"

#include <QString>

class CPatternCounter
{
    MultiPatternSearcher m_searcher, m_searcherRaw;
    bool m_bCaseSensitive;
    int m_nOverlap;
    PatternMatchContainer m_foundPatterns;
    QString m_PreChunk;

    bool CheckPatterns( MultiPatternSearcher& searcher, const QByteArray& array );

public:
    CPatternCounter( const QStringList& listPatterns, bool bCaseSensitive, int nOverlap );
    void ClearResult();
    bool OnChunk( const QString& strChunk );
    bool OnChunkIsRaw( const QByteArray& array );
    bool MatchedOk();
    bool SomePatterns();
};

#endif
