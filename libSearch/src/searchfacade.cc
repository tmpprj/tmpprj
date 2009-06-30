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

    m_searcher.SigError().connect( boost::bind( &CSearchFacade::OnError, this, _1, _2 ) );
    m_extractor.SigError().connect( boost::bind( &CSearchFacade::OnError, this, _1, _2 ) );
    m_matcher.SigError().connect( boost::bind( &CSearchFacade::OnError, this, _1, _2 ) );
}

void CSearchFacade::Start( const QString& strPath, const QStringList& patterns,
        const QStringList& listMasks, bool bCaseSensitive )
{
    CLog() << "CSearchFacade::Start: pattern count - " << patterns.size() << std::endl;
    
    m_matcher.SetSearchParameters( patterns, bCaseSensitive );
    m_searcher.StartSearch( strPath, listMasks );
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

void CSearchFacade::OnError( const QString& strFilename, const QString& strError )
{
    m_sigError( strFilename, strError );
}

boost::signals2::signal1< void, const QString& >& CSearchFacade::SigFileFound()
{
    return m_searcher.SigFileFound();
}

boost::signals2::signal1< void, const CPlainTextExtractor::structFileData& >& CSearchFacade::SigDataObtained()
{
    return m_extractor.SigDataObtained();
}

boost::signals2::signal1< void, const CPatternMatcher::structFindData& >& CSearchFacade::SigFileMatched()
{
    return m_matcher.SigFileMatched();
}

boost::signals2::signal0< void >& CSearchFacade::SigSearchDone()
{
    return m_sigDone;
}

boost::signals2::signal2< void, const QString&, const QString& >& CSearchFacade::SigError()
{
    return m_sigError;
}

