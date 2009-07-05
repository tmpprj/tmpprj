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
    int nFoundPatterns = m_searcher.FindPatterns( strData, chunkPatterns );

    m_foundPatterns.insert( chunkPatterns.begin(), chunkPatterns.end() );

    bool bRet = m_foundPatterns.size() < m_searcher.GetPatternCount();
    CLog( debug ) << "Processing chunk: size( " << strChunk.size() << " ) " << bRet << '\t' << m_foundPatterns.size() << '\t' << m_searcher.GetPatternCount() << std::endl;

    return bRet;
}

bool CPatternCounter::MatchedOk()
{
    return m_foundPatterns.size() >= m_searcher.GetPatternCount();
}
