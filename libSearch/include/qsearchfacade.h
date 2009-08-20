#ifndef QSEARCHFACADE_H
#define QSEARCHFACADE_H

#include "searchfacade.h"
#include <QThread>
#include <boost/thread.hpp>
#include <mt_queue.hpp>

class QSearchFacade : public QThread
{
    Q_OBJECT

    CSearchFacade m_search;
    boost::mutex m_mtxSig;
    bool m_active;

    struct SignalRec
    {
        int nFunc;
        QString strFileName;
        QString strError;
    };

    mt_queue< SignalRec > m_queue;

    void run();

    void OnFileFound( const QString& strFileName );
    void OnFileProcessing( const QString& strFileName );
    void OnFileMatched( const QString& strFileName );
    void OnSearchStart();
    void OnSearchDone();
    void OnError( const QString& strFileName, const QString& strError );
public:
    QSearchFacade( QObject* parent = 0 );
    ~QSearchFacade();
    void Start( const SearchOptions& options );
    void Stop();

Q_SIGNALS:
    void fileFound( const QString& strFileName );
    void fileProcessing( const QString& strFileName );
    void fileMatched( const QString& strFileName ); 
    void searchStart();
    void searchDone();
    void error( const QString& strFileName, const QString& strError );
};

#endif
