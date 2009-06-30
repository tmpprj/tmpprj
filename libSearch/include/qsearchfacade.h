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
    void OnDataObtained( const CPlainTextExtractor::structFileData& );
    void OnFileMatched( const CPatternMatcher::structFindData& );
    void OnSearchDone();
    void OnError( const QString& strFileName, const QString& strError );
public:
    QSearchFacade( QObject* parent = 0 );
    CSearchFacade& GetSearcher();

Q_SIGNALS:
    void fileFound( const QString& strFileName );
    void dataObtained( const QString& strFileName, const QString& strFileData );
    void fileMatched( const QString& strFileName, bool bFound ); 
    void searchDone();
    void error( const QString& strFileName, const QString& strError );
};

#endif
