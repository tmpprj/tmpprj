#include "qsearchfacade.h"

#include <log.hpp>

QSearchFacade::QSearchFacade( QObject* parent )
    : QObject( parent )
{
    m_search.SigFileMatched().connect( boost::bind( &QSearchFacade::OnFileMatched, this, _1 ) );
    m_search.SigSearchDone().connect( boost::bind( &QSearchFacade::OnSearchDone, this ) );
    m_search.SigDataObtained().connect( boost::bind( &QSearchFacade::OnDataObtained, this, _1 ) );
    m_search.SigFileFound().connect( boost::bind( &QSearchFacade::OnFileFound, this, _1 ) );
}

CSearchFacade& QSearchFacade::GetSearcher()
{
    return m_search;
}

void QSearchFacade::OnFileFound( const QString& strFileName )
{
    Q_EMIT fileFound( strFileName );
}

void QSearchFacade::OnDataObtained( const CPlainTextExtractor::structFileData& fileData )
{
    Q_EMIT dataObtained( fileData.strFileName, fileData.strFileData );
}

void QSearchFacade::OnFileMatched( const CPatternMatcher::structFindData& findData )
{
    Q_EMIT fileMatched( findData.strFileName, findData.bFound );
}

void QSearchFacade::OnSearchDone()
{
    Q_EMIT searchDone();
}

