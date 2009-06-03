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

class CPatternMatcher
{
    typedef std::auto_ptr< boost::thread > ThreadPtr_t;
    ThreadPtr_t m_ptrThread;
    PatternsContainer m_patterns;
    MultiPatternSearcher m_searcher;
    boost::mutex m_mutAccess;
    boost::signal2< void , const std::string&, bool > m_sigFileProcessed;

    struct FileInfo
    {
        std::string strFilename;
        QString strFiledata;
    };
    mt_queue< FileInfo > m_Queue;
        
    void ThreadFunc( boost::mutex* pmtxThreadStarted );

public:
    CPatternMatcher();
    void SetPatterns( const PatternsContainer& patterns );
    void OnNewFile( const std::string& strFilename, const QString& strFiledata );
    void OnStop();
    boost::signal2< void, const std::string&, bool >& SigFileProcessed();
    ~CPatternMatcher();
};

#endif

