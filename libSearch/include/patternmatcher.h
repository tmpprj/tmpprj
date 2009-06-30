#ifndef _PATTERNMATCHER_H_
#define _PATTERNMATCHER_H_

#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include <vector>
#include <string>
#include <memory>
#include <mt_queue.hpp>
#include <QString>

#include "multipatternsearcher.h"
#include "datahandler.hpp"
#include "plaintextextractor.h"

class CPatternMatcher: public CDataHandler< CPlainTextExtractor::structFileData >
{
public:

    CPatternMatcher();
    
    struct structFindData
    {
        const QString strFileName;
        bool bFound;
    };

    void SetSearchParameters( const QStringList& listPatterns, bool bCaseSensitive );
    boost::signals2::signal1< void, const structFindData& >& SigFileMatched();
    virtual void WorkerFunc( const CPlainTextExtractor::structFileData& Data );

private:

    bool m_bCaseSensitive;
    MultiPatternSearcher m_searcher;
    boost::signals2::signal1< void , const structFindData& > m_sigFileMatched;

    bool CheckData( const QString& strFileData );
};

#endif

