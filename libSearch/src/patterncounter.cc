#include "patterncounter.h"
#include "libsearch_common.h"
#include <log.hpp>

CPatternCounter::CPatternCounter( MultiPatternSearcher& searcher, bool bCaseSensitive, int nOverlap )
    : m_searcher( searcher ),
      m_bCaseSensitive( bCaseSensitive ),
      m_nOverlap( nOverlap )
{
}

bool CPatternCounter::OnChunk( const QString& strChunk )
{
    QByteArray array = StringToCommon( m_strPreBlock + strChunk, m_bCaseSensitive );
    std::string strData = std::string( ( const char* )array, array.size() );
    
    PatternMatchContainer chunkPatterns;
    m_searcher.FindPatterns( strData, chunkPatterns );

    m_foundPatterns.insert( chunkPatterns.begin(), chunkPatterns.end() );
    
    CLog( debug ) << "Chunk patterns: " << chunkPatterns.size();
    CLog( debug ) << "Found patterns: " << m_foundPatterns.size();

    m_strPreBlock = strChunk.right( m_nOverlap );

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
