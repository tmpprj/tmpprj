#ifndef DOCUMENTCHECKER_H
#define DOCUMENTCHECKER_H

#include "datahandler.hpp"
#include "multipatternsearcher.h"
#include "plaintextextractor.h"
#include "patterncounter.h"
#include "searchoptions.h"

#include <QString>
#include <QStringList>


class CDocumentChecker : public CDataHandler< QString >
{
public:
    CDocumentChecker();
    void SetSearchParameters( const SearchOptions& );

    boost::signals2::signal1< void, const QString& >& SigFileProcessing();
    boost::signals2::signal1< void, const QString& >& SigFileMatched();

private:
    virtual void WorkerFunc( const QString& strFileName );

    std::auto_ptr< CPatternCounter > m_ptrCounter;
    boost::signals2::signal1< void, const QString& > m_sigFileProcessing;
    boost::signals2::signal1< void, const QString& > m_sigFileMatched;
    SearchOptions m_Options;
};

#endif
