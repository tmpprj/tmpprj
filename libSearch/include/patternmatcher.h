#ifndef _PATTERNMATCHER_H_
#define _PATTERNMATCHER_H_

#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <vector>
#include <string>
#include <memory>
#include <mt_queue.hpp>
#include <QString>

#include "searchdefines.h"
#include "multipatternsearcher.h"
#include "datahandler.hpp"
#include "plaintextextractor.h"

class CPatternMatcher: public CDataHandler< CPlainTextExtractor::structFileData >
{
public:

    struct structFindData
    {
        const QString strFileName;
        bool bFound;
    };

    void SetPatterns( const PatternsContainer& patterns );

    boost::signal1< void, const structFindData& >& SigFileMatched();

    virtual void WorkerFunc( const CPlainTextExtractor::structFileData& Data );

private:

    MultiPatternSearcher m_searcher;
    boost::signal1< void , const structFindData& > m_sigFileMatched;

};

#endif

