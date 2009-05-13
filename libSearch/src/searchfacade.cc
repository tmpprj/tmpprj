#include "searchfacade.h"
#include "filesearcher.h"

CSearchFacade::CSearchFacade()
{
    m_sigStop.connect( 0, boost::bind( &CFileSearcher::OnStop, &m_searcher ) );
    m_sigStop.connect( 1, boost::bind( &CPlainTextExtractor::OnStop, &m_extractor ) );
    m_sigStop.connect( 2, boost::bind( &CPatternMatcher::OnStop, &m_matcher ) );

    m_searcher.SigFileProcessed().connect( boost::bind( &CPlainTextExtractor::OnNewFile, &m_extractor, _1 ) );
    m_extractor.SigDataObtained().connect( boost::bind( &CPatternMatcher::OnNewFile, &m_matcher, _1, _2 ) );
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

boost::signal1< void, const std::string& >& CSearchFacade::SigFileFound()
{
    return m_searcher.SigFileProcessed();
}

boost::signal2< void, const std::string&, const QString& >& CSearchFacade::SigFileProcessed()
{
    return m_extractor.SigDataObtained();
}

boost::signal2< void, const std::string&, bool >& CSearchFacade::SigFileMatched()
{
    return m_matcher.SigFileProcessed();
}

