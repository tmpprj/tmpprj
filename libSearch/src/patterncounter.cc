#include "patterncounter.h"
#include "libsearch_common.h"
#include <log.h>

CPatternCounter::CPatternCounter( const QStringList& listPatterns, bool bCaseSensitive, int nOverlap )
: m_bCaseSensitive( bCaseSensitive ),
  m_nOverlap( nOverlap )
{
    PatternsContainer patterns;
    ConvertListToPatterns( listPatterns, m_bCaseSensitive, false, patterns );
    m_searcher.LoadPatterns( patterns );
    
    PatternsContainer patternsRaw;
    ConvertListToPatterns( listPatterns, m_bCaseSensitive, true, patternsRaw );
    m_searcherRaw.LoadPatterns( patternsRaw );
}

void CPatternCounter::ClearResult()
{
    m_foundPatterns.clear();
    m_PreChunk.clear();
}

bool CPatternCounter::CheckPatterns( MultiPatternSearcher& searcher, const QByteArray& array )
{
    std::string strData = std::string( array.data(), array.size() );
    
    PatternMatchContainer chunkPatterns;
    searcher.FindPatterns( strData, chunkPatterns );

    m_foundPatterns.insert( chunkPatterns.begin(), chunkPatterns.end() );
    
    CLog( Debug ) << "Chunk patterns: " << chunkPatterns.size();
    CLog( Debug ) << "Found patterns: " << m_foundPatterns.size();

    return ( m_foundPatterns.size() < searcher.GetPatternCount() );
}

bool CPatternCounter::OnChunk( const QString& strChunk )
{
    QByteArray array = StringToCommon( m_PreChunk + strChunk, m_bCaseSensitive );
    bool ret = CheckPatterns( m_searcher, array );
    m_PreChunk = strChunk;

    return ret;
}

bool CPatternCounter::OnChunkIsRaw( const QByteArray& array )
{
    QString strChunk( array );
    return OnChunk( strChunk );
}

bool CPatternCounter::MatchedOk()
{
    return m_foundPatterns.size() >= m_searcher.GetPatternCount();
}

bool CPatternCounter::SomePatterns()
{
    return m_searcher.GetPatternCount() > 0;
}
