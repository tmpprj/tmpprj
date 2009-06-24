#ifndef _SEARCHFACADE_H_
#define _SEARCHFACADE_H_

#include <string>
#include <boost/utility.hpp>
#include <boost/signal.hpp>
#include <QString>

#include "filesearcher.h"
#include "plaintextextractor.h"
#include "patternmatcher.h"
#include "multipatternsearcher.h"

class CSearchFacade : public boost::noncopyable
{
    CFileSearcher m_searcher;
    CPlainTextExtractor m_extractor;
    CPatternMatcher m_matcher;
    boost::signal0< void > m_sigStop;
    boost::signal0< void > m_sigDone;

    void OnSomeQueueEmpty();

public:
    CSearchFacade();
    void Start( const QString& strPath, const QStringList& patterns, const QStringList& vMasks, bool bCaseSensitive );
    void Stop();
    ~CSearchFacade();

    boost::signal1< void, const QString& >& SigFileFound();
    boost::signal1< void, const CPlainTextExtractor::structFileData& >& SigDataObtained();
    boost::signal1< void, const CPatternMatcher::structFindData& >& SigFileMatched();
    boost::signal0< void >& SigSearchDone();
};


#endif

