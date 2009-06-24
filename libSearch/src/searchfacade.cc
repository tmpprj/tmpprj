#include "searchfacade.h"
#include "filesearcher.h"
#include "log.hpp"

CSearchFacade::CSearchFacade()
{
    m_sigStop.connect( 0, boost::bind( &CFileSearcher::OnStop, &m_searcher ) );
    m_sigStop.connect( 1, boost::bind( &CPlainTextExtractor::OnStop, &m_extractor ) );
    m_sigStop.connect( 2, boost::bind( &CPatternMatcher::OnStop, &m_matcher ) );

    m_searcher.SigFileFound().connect( boost::bind( &CPlainTextExtractor::OnData, &m_extractor, _1 ) );
    m_extractor.SigDataObtained().connect( boost::bind( &CPatternMatcher::OnData, &m_matcher, _1 ) );
    
    m_searcher.SigQueueEmpty().connect( boost::bind( &CSearchFacade::OnSomeQueueEmpty, this ) );
    m_extractor.SigQueueEmpty().connect( boost::bind( &CSearchFacade::OnSomeQueueEmpty, this ) );
    m_matcher.SigQueueEmpty().connect( boost::bind( &CSearchFacade::OnSomeQueueEmpty, this ) );
}

void CSearchFacade::Start( const QString& strPath, const PatternsContainer& patterns, const Masks_t& vMasks )
{
    CLog() << "CSearchFacade::Start" << std::endl;
    m_matcher.SetPatterns( patterns );
    m_searcher.StartSearch( strPath, vMasks );
}

void CSearchFacade::Stop()
{
    m_sigStop();
}

CSearchFacade::~CSearchFacade()
{
    Stop();
}

void CSearchFacade::OnSomeQueueEmpty()
{
    if( m_searcher.IsQueueEmpty() && m_extractor.IsQueueEmpty() && m_matcher.IsQueueEmpty() )
        m_sigDone();
}

boost::signal1< void, const QString& >& CSearchFacade::SigFileFound()
{
    return m_searcher.SigFileFound();
}

boost::signal1< void, const CPlainTextExtractor::structFileData& >& CSearchFacade::SigDataObtained()
{
    return m_extractor.SigDataObtained();
}

boost::signal1< void, const CPatternMatcher::structFindData& >& CSearchFacade::SigFileMatched()
{
    return m_matcher.SigFileMatched();
}

boost::signal0< void >& CSearchFacade::SigSearchDone()
{
    return m_sigDone;
}

