#ifndef _FILE_SEARCHER_H_
#define _FILE_SEARCHER_H_

#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <vector>
#include <string>
#include <memory>
#include <QString>
#include <QStringList>

#include "datahandler.hpp"


namespace FileSearcher
{
    struct structParams
    {
        QString strPath;
        QStringList listMasks;
    };
}

class CFileSearcher: public CDataHandler< FileSearcher::structParams >
{
    boost::signal1< void , const QString& > m_sigFileFound;

    void Search( const QString& strPath, const QStringList& listMasks );

    virtual void WorkerFunc( const FileSearcher::structParams& Params );

public:

    void StartSearch( const QString& strPath, const QStringList& listMasks );

    boost::signal1< void, const QString& >& SigFileFound();
};

#endif

