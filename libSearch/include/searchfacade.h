#ifndef _SEARCHFACADE_H_
#define _SEARCHFACADE_H_

#include <string>
#include <boost/utility.hpp>
#include <boost/signal.hpp>
#include <QString>

#include "searchdefines.h"
#include "filesearcher.h"
#include "plaintextextractor.h"

class CSearchFacade : public boost::noncopyable
{
    CFileSearcher m_searcher;
    CPlainTextExtractor m_extractor;
    boost::signal0< void > m_sigStop;

public:
    CSearchFacade();
    void Start( const std::string& strPath, const Masks_t& vMasks );
    void Stop();

    boost::signal1< void, const std::string& >& SigFileFound();
    boost::signal1< void, const QString& >& SigFileProcessed();

/* TODO: Future work
    boost::singal0< void >& SigDone();
*/
};


#endif

