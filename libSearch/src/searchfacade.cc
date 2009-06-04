#include "searchfacade.h"
#include "filesearcher.h"

CSearchFacade::CSearchFacade()
{
    m_sigStop.connect( 0, boost::bind( &CFileSearcher::OnStop, &m_searcher ) );
    m_sigStop.connect( 1, boost::bind( &CPlainTextExtractor::OnStop, &m_extractor ) );
    m_sigStop.connect( 2, boost::bind( &CPatternMatcher::OnStop, &m_matcher ) );

    m_searcher.SigFileProcessed().connect( boost::bind( &CPlainTextExtractor::OnData, &m_extractor, _1 ) );
    m_extractor.SigDataObtained().connect( boost::bind( &CPatternMatcher::OnData, &m_matcher, _1 ) );
}

void CSearchFacade::Start( const std::string& strPath, const PatternsContainer& patterns, const Masks_t& vMasks )
{
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

boost::signal1< void, const QString& >& CSearchFacade::SigFileFound()
{
    return m_searcher.SigFileProcessed();
}

boost::signal1< void, const CPlainTextExtractor::structFileData& >& CSearchFacade::SigFileProcessed()
{
    return m_extractor.SigDataObtained();
}

boost::signal1< void, const CPatternMatcher::structFindData& >& CSearchFacade::SigFileMatched()
{
    return m_matcher.SigFileProcessed();
}

