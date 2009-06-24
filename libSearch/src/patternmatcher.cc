#include "patternmatcher.h"
#include "log.hpp"

void CPatternMatcher::WorkerFunc( const CPlainTextExtractor::structFileData& Data )
{
    CLog() << "Pattern count: " << m_searcher.GetPatternCount() << std::endl;
    if( m_searcher.GetPatternCount() == 0 )
    {
        CLog() << __FUNCTION__ << ": Pattern count is NULL" << std::endl;
        return;
    }

    int nFoundPatterns = m_searcher.FindPatterns( std::string( ( const char* )Data.strFileData.utf16(), 
                                                               Data.strFileData.size() * 2 ) );
    bool bFileGood = ( ( size_t )nFoundPatterns == m_searcher.GetPatternCount() );
    structFindData FindData = { Data.strFileName, bFileGood };
    m_sigFileMatched( FindData );
}

void CPatternMatcher::SetPatterns( const PatternsContainer& patterns )
{
    m_searcher.LoadPatterns( patterns );
}

boost::signal1< void, const CPatternMatcher::structFindData& >& CPatternMatcher::SigFileMatched()
{
    return m_sigFileMatched;
}

