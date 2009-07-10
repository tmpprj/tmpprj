#include "patterncounter.h"

#include <log.hpp>

CPatternCounter::CPatternCounter( MultiPatternSearcher& searcher )
    : m_searcher( searcher )
{
}

bool CPatternCounter::OnChunk( const QString& strChunk )
{
    PatternMatchContainer chunkPatterns;
    std::string strData = std::string( ( const char* )strChunk.utf16(), strChunk.size() * 2 );
    m_searcher.FindPatterns( strData, chunkPatterns );

    m_foundPatterns.insert( chunkPatterns.begin(), chunkPatterns.end() );

    return ( m_foundPatterns.size() < m_searcher.GetPatternCount() );
}

bool CPatternCounter::MatchedOk()
{
    return m_foundPatterns.size() >= m_searcher.GetPatternCount();
}

bool CPatternCounter::SomePatterns()
{
    return m_searcher.GetPatternCount() > 0;
}
