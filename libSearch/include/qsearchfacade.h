#ifndef QSEARCHFACADE_H
#define QSEARCHFACADE_H

#include "searchfacade.h"
#include <QObject>
#include <boost/thread.hpp>

class QSearchFacade : public QObject
{
    Q_OBJECT

    CSearchFacade m_search;
    boost::mutex m_mtxSig;

    void OnFileFound( const QString& strFilename );
    void OnFileProcessing( const QString& strFilename );
    void OnFileMatched( const QString& strFilename );
    void OnSearchDone();
    void OnError( const QString& strFileName, const QString& strError );
public:
    QSearchFacade( QObject* parent = 0 );
    CSearchFacade& GetSearcher();

Q_SIGNALS:
    void fileFound( const QString& strFileName );
    void fileProcessing( const QString& strFileName );
    void fileMatched( const QString& strFileName ); 
    void searchDone();
    void error( const QString& strFileName, const QString& strError );
};

#endif
