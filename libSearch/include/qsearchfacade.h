#ifndef QSEARCHFACADE_H
#define QSEARCHFACADE_H

#include "searchfacade.h"
#include <QObject>

class QSearchFacade : public QObject
{
    Q_OBJECT

    CSearchFacade m_search;

    void OnFileFound( const QString& strFilename );
    void OnFileProcessed( const CPlainTextExtractor::structFileData& );
    void OnFileMatched( const CPatternMatcher::structFindData& );
    void OnSearchDone();
public:
    QSearchFacade( QObject* parent = 0 );
    CSearchFacade& GetSearcher();

Q_SIGNALS:
    void fileFound( const QString& strFileName );
    void fileProcessed( const QString& strFileName, const QString& strFileData );
    void fileMatched( const QString& strFileName, bool bFound ); 
    void searchDone();
};

#endif
