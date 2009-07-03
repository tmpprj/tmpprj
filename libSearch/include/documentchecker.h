#ifndef DOCUMENTCHECKER_H
#define DOCUMENTCHECKER_H

#include "datahandler.hpp"
#include "multipatternsearcher.h"
#include "plaintextextractor.h"

#include <QString>
#include <QStringList>

class CDocumentChecker : public CDataHandler< QString >
{
public:
    CDocumentChecker();
    void SetSearchParameters( const QStringList& listPatterns, bool bCaseSensitive );

    boost::signals2::signal1< void, const QString& >& SigFileProcessing();
    boost::signals2::signal1< void, const QString& >& SigFileMatched();

private:
    virtual void WorkerFunc( const QString& strFileName );

    MultiPatternSearcher m_searcher;
    bool m_bCaseSensitive;
    boost::signals2::signal1< void, const QString& > m_sigFileProcessing;
    boost::signals2::signal1< void, const QString& > m_sigFileMatched;
};

#endif
