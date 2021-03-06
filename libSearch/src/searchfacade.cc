#include "searchfacade.h"
#include "filesearcher.h"
#include "documentchecker.h"
#include "log.h"

CSearchFacade::CSearchFacade()
{
    m_sigStop.connect( 0, boost::bind( &CFileSearcher::OnStop, &m_searcher ) );
    m_sigStop.connect( 1, boost::bind( &CDocumentChecker::OnStop, &m_checker ) );

    m_searcher.SigFileFound().connect( boost::bind( &CDocumentChecker::OnData, &m_checker, _1 ) );
    
    m_searcher.SigQueueEmpty().connect( boost::bind( &CSearchFacade::OnSomeQueueEmpty, this ) );
    m_checker.SigQueueEmpty().connect( boost::bind( &CSearchFacade::OnSomeQueueEmpty, this ) );

    m_searcher.SigError().connect( boost::bind( &CSearchFacade::OnError, this, _1, _2 ) );
    m_checker.SigError().connect( boost::bind( &CSearchFacade::OnError, this, _1, _2 ) );
}

CSearchFacade::~CSearchFacade()
{
    // Disconnecting signals to not call OnSomeQueueEmpty when destroying objects separately
    m_searcher.SigQueueEmpty().disconnect_all_slots();
    m_checker.SigQueueEmpty().disconnect_all_slots();
    
    Stop();
}

void CSearchFacade::Start( const SearchOptions& options )
{
    CLog(Debug) << "CSearchFacade::Start: pattern count - " << options.listPatterns.size();
    
    m_sigStart();
    m_checker.SetSearchParameters( options );
    m_searcher.StartSearch( options.strPath, options.listMasks, options.bRecursive, 
                            options.stMinFileSize, options.stMaxFileSize );
}

void CSearchFacade::Stop()
{
    m_sigStop();
}

void CSearchFacade::OnSomeQueueEmpty()
{
    if( m_searcher.IsQueueEmpty() && m_checker.IsQueueEmpty() )
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

boost::signals2::signal1< void, const QString& >& CSearchFacade::SigFileProcessing()
{
    return m_checker.SigFileProcessing();
}

boost::signals2::signal1< void, const QString& >& CSearchFacade::SigFileMatched()
{
    return m_checker.SigFileMatched();
}

boost::signals2::signal0< void >& CSearchFacade::SigSearchStart()
{
    return m_sigStart;
}

boost::signals2::signal0< void >& CSearchFacade::SigSearchDone()
{
    return m_sigDone;
}

boost::signals2::signal2< void, const QString&, const QString& >& CSearchFacade::SigError()
{
    return m_sigError;
}

