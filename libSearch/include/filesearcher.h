#ifndef _FILE_SEARCHER_H_
#define _FILE_SEARCHER_H_

#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <vector>
#include <string>
#include <memory>
#include <QString>

#include "searchdefines.h"
#include "datahandler.hpp"


namespace FileSearcher
{
    struct structParams
    {
        QString strPath;
        Masks_t vMasks;
    };
}

class CFileSearcher: public CDataHandler< FileSearcher::structParams >
{
    boost::signal1< void , const QString& > m_sigFileProcessed;

    void Search( const QString& strPath, const Masks_t& vMasks );

    virtual void WorkerFunc( const FileSearcher::structParams& Params );

public:

    void StartSearch( const QString& strPath, const Masks_t& vMasks );

    boost::signal1< void, const QString& >& SigFileProcessed();
};

#endif

