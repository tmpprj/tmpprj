#ifndef _SEARCHFACADE_H_
#define _SEARCHFACADE_H_

#include <string>
#include <boost/utility.hpp>
#include <boost/signal.hpp>

#include "searchdefines.h"
#include "filesearcher.h"

class SearchFacade : public boost::noncopyable
{
    FileSearcher m_searcher;
    boost::signal0< void > m_sigStop;

public:
    void StartSearch( const std::string& strPath, const Masks_t& vMasks );
    void Stop();

    boost::signal0< void >& SigStop();
    boost::signal1< void, const std::string& >& SigFileProcessed();

/* TODO: Future work
    boost::singal0< void >& SigDone();
*/
};


#endif

