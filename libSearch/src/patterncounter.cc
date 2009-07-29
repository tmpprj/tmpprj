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
    QByteArray array = StringToCommon( strChunk, m_bCaseSensitive );
    return OnChunkIsRaw( array );
}

bool CPatternCounter::OnChunkIsRaw( const QByteArray& array )
{
    const QByteArray arraySearch = m_PreBlock + array;
    std::string strData = std::string( arraySearch.data(), arraySearch.size() );
    
    PatternMatchContainer chunkPatterns;
    m_searcher.FindPatterns( strData, chunkPatterns );

    m_foundPatterns.insert( chunkPatterns.begin(), chunkPatterns.end() );
    
    CLog( debug ) << "Chunk patterns: " << chunkPatterns.size();
    CLog( debug ) << "Found patterns: " << m_foundPatterns.size();

    m_PreBlock = array;

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
