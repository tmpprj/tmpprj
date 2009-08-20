#include "qsearchfacade.h"

#include <log.h>
#include <QThread>

QSearchFacade::QSearchFacade( QObject* parent )
    : QThread( parent ),
      m_active( true ),
      m_queue( -1 )
{
    m_search.SigFileFound().connect( boost::bind( &QSearchFacade::OnFileFound, this, _1 ) );
    m_search.SigFileProcessing().connect( boost::bind( &QSearchFacade::OnFileProcessing, this, _1 ) );
    m_search.SigFileMatched().connect( boost::bind( &QSearchFacade::OnFileMatched, this, _1 ) );
    m_search.SigSearchStart().connect( boost::bind( &QSearchFacade::OnSearchStart, this ) );
    m_search.SigSearchDone().connect( boost::bind( &QSearchFacade::OnSearchDone, this ) );
    m_search.SigError().connect( boost::bind( &QSearchFacade::OnError, this, _1, _2 ) );
    start();
}

QSearchFacade::~QSearchFacade()
{
    m_active = false;
    m_queue.push( SignalRec() );
    wait();
}

void QSearchFacade::Start( const SearchOptions& options )
{
    OnSearchStart();
    m_search.Start( options );
}

void QSearchFacade::Stop()
{
    m_search.Stop();
    m_queue.clear();
    OnSearchDone();
}

void QSearchFacade::run()
{
    while( true )
    {
        SignalRec rec = m_queue.front( true );
        if( !m_active )
            break;

        CLog( Debug ) << "Facade: " << rec.nFunc << std::endl;
        switch( rec.nFunc )
        {
            case 1:
                Q_EMIT fileFound( rec.strFileName );
                break;
            case 2:
                Q_EMIT fileProcessing( rec.strFileName );
                break;
            case 3:
                Q_EMIT fileMatched( rec.strFileName );
                break;
            case 4:
                Q_EMIT searchStart();
                break;
            case 5:
                Q_EMIT searchDone();
                break;
            case 6:
                Q_EMIT error( rec.strFileName, rec.strError );
                break;
        }
    }
}

void QSearchFacade::OnFileFound( const QString& strFileName )
{
    SignalRec rec = { 1, strFileName, "" };
    m_queue.push( rec );
}

void QSearchFacade::OnFileProcessing( const QString& strFileName )
{
    SignalRec rec = { 2, strFileName, "" };
    m_queue.push( rec );
}

void QSearchFacade::OnFileMatched( const QString& strFileName )
{
    SignalRec rec = { 3, strFileName, "" };
    m_queue.push( rec );
}

void QSearchFacade::OnSearchStart()
{
    SignalRec rec = { 4, "", "" };
    m_queue.push( rec );
}

void QSearchFacade::OnSearchDone()
{
    SignalRec rec = { 5, "", "" };
    m_queue.push( rec );
}

void QSearchFacade::OnError( const QString& strFileName, const QString& strError )
{
    SignalRec rec = { 6, strFileName, strError };
    m_queue.push( rec );
}
