#ifndef _FILE_SEARCHER_H_
#define _FILE_SEARCHER_H_

#include <QtCore/QtCore>
#include <boost/thread.hpp>
#include <string>
#include <memory>
#include <set>

class FileSearcher
{
    typedef std::auto_ptr< boost::thread > ThreadPtr_t;
    ThreadPtr_t m_ptrSearchThread;

    void Search( const QDir& path, const QStringList& listMasks );
    void SearchFunc( const QDir& path, const QStringList& listMasks, boost::condition_variable* pvarStarted );
    void StopSearch();

public:
    void StartSearch( const QDir& path, const QStringList& listMasks );
    const QString GetNextFinded();
    ~FileSearcher();
};

#endif

