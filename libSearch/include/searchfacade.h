#ifndef _SEARCHFACADE_H_
#define _SEARCHFACADE_H_

#include <string>
#include <boost/utility.hpp>
#include <boost/signals2.hpp>
#include <QString>

#include "filesearcher.h"
#include "plaintextextractor.h"
#include "patternmatcher.h"
#include "multipatternsearcher.h"

struct SearchOptions
{
    QString strPath;
    QStringList listPatterns;
    QStringList listMasks;
    bool bCaseSensitive;
    bool bRecursive;
};


class CSearchFacade : public boost::noncopyable
{
    CFileSearcher m_searcher;
    CPlainTextExtractor m_extractor;
    CPatternMatcher m_matcher;
    boost::signals2::signal0< void > m_sigStop;
    boost::signals2::signal0< void > m_sigDone;
    boost::signals2::signal2< void, const QString&, const QString& > m_sigError;

    void OnSomeQueueEmpty();
    void OnError( const QString& strFilename, const QString& strError );

public:
    CSearchFacade();
    void Start( const SearchOptions& options );
    void Stop();
    ~CSearchFacade();

    boost::signals2::signal1< void, const QString& >& SigFileFound();
    boost::signals2::signal1< void, const QString& >& SigFileProcessing();
    boost::signals2::signal1< void, const CPlainTextExtractor::structFileData& >& SigDataObtained();
    boost::signals2::signal1< void, const CPatternMatcher::structFindData& >& SigFileMatched();
    boost::signals2::signal0< void >& SigSearchDone();
    boost::signals2::signal2< void, const QString&, const QString& >& SigError();
};


#endif

