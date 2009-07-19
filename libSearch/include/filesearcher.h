#ifndef _FILE_SEARCHER_H_
#define _FILE_SEARCHER_H_

#include <boost/thread.hpp>
#include <boost/signals2.hpp>
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
        bool bRecursive;
        size_t stMinFileSize;
        size_t stMaxFileSize;
    };
}

class CFileSearcher: public CDataHandler< FileSearcher::structParams >
{
    boost::signals2::signal1< void , const QString& > m_sigFileFound;

    void Search( const QString& strPath, const QStringList& listMasks, bool bRecursive, size_t stMinFileSize, size_t stMaxFileSize );

    virtual void WorkerFunc( const FileSearcher::structParams& Params );

public:
    CFileSearcher();

    void StartSearch( const QString& strPath, const QStringList& listMasks, bool bRecursive, size_t stMinFileSize, size_t stMaxFileSize );

    boost::signals2::signal1< void, const QString& >& SigFileFound();
};

#endif

