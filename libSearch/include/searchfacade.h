#ifndef _SEARCHFACADE_H_
#define _SEARCHFACADE_H_

#include <string>
#include <boost/utility.hpp>
#include <boost/signal.hpp>
#include <QString>

#include "searchdefines.h"
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

public:
    CSearchFacade();
    void Start( const std::string& strPath, const PatternsContainer& patterns, const Masks_t& vMasks );
    void Stop();
    ~CSearchFacade();

    boost::signal1< void, const std::string& >& SigFileFound();
    boost::signal2< void, const std::string&, const QString& >& SigFileProcessed();
    boost::signal2< void, const std::string&, bool >& SigFileMatched();

/* TODO: Future work
    boost::singal0< void >& SigDone();
*/
};


#endif

