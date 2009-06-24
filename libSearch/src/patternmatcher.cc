#include "patternmatcher.h"
#include "log.hpp"
#include "libsearch_common.h"

CPatternMatcher::CPatternMatcher()
: m_bCaseSensitive( false )
{
}

void CPatternMatcher::WorkerFunc( const CPlainTextExtractor::structFileData& Data )
{
    CLog() << "Pattern count: " << m_searcher.GetPatternCount() << std::endl;

    bool bFileGood;
    if( m_searcher.GetPatternCount() == 0 )
        bFileGood = true;
    else
        bFileGood =CheckData( Data.strFileData );

    structFindData FindData = { Data.strFileName, bFileGood };
    m_sigFileMatched( FindData );
}

bool CPatternMatcher::CheckData( const QString& strFileData )
{
    QString strDataToCheck;
    if( m_bCaseSensitive )
        strDataToCheck = strFileData;
    else
        strDataToCheck = strFileData.toLower();

    int nFoundPatterns = m_searcher.FindPatterns( 
            std::string( ( const char* )strDataToCheck.utf16(), strDataToCheck.size() * 2 ) );

    return ( ( size_t )nFoundPatterns == m_searcher.GetPatternCount() );
}

void CPatternMatcher::SetSearchParameters( const QStringList& listPatterns, bool bCaseSensitive )
{
    m_bCaseSensitive = bCaseSensitive;

    PatternsContainer patterns;
    ConvertListToPatterns( listPatterns, m_bCaseSensitive, patterns );
    m_searcher.LoadPatterns( patterns );
}

boost::signal1< void, const CPatternMatcher::structFindData& >& CPatternMatcher::SigFileMatched()
{
    return m_sigFileMatched;
}

