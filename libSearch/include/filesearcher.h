#ifndef _FILE_SEARCHER_H_
#define _FILE_SEARCHER_H_

#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <vector>
#include <string>
#include <memory>

#include "searchdefines.h"
#include "mt_queue.hpp"

class CFileSearcher
{
    typedef std::auto_ptr< boost::thread > ThreadPtr_t;
    ThreadPtr_t m_ptrSearchThread;
    boost::signal1< void , const std::string& > m_sigFileProcessed;

    void Search( const std::string& strPath, const Masks_t& vMasks );
    void SearchFunc( const std::string& strPath, const Masks_t& vMasks, boost::condition_variable* pvarStarted );

public:
    void StartSearch( const std::string& strPath, const Masks_t& vMasks );
    void OnStop();
    boost::signal1< void, const std::string& >& SigFileProcessed();
    ~CFileSearcher();
};

#endif

