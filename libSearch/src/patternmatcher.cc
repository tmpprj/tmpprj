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
    if( m_searcher.GetPatternCount() == 0 )
    {
        CLog() << __FUNCTION__ << ": Pattern count is NULL" << std::endl;
        return;
    }

    QString strData;
    if( m_bCaseSensitive )
        strData = Data.strFileData;
    else
        strData = Data.strFileData.toLower();

    int nFoundPatterns = m_searcher.FindPatterns( std::string( ( const char* )strData.utf16(), strData.size() * 2 ) );
    bool bFileGood = ( ( size_t )nFoundPatterns == m_searcher.GetPatternCount() );
    structFindData FindData = { Data.strFileName, bFileGood };
    m_sigFileMatched( FindData );
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

