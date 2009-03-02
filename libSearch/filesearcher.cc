#include "filesearcher.h"


using namespace std;

void FileSearcher::Search( const QDir& path, const QStringList& listMasks )
{
    QFileInfoList files = path.entryInfoList( listMasks, QDir::AllDirs | QDir::Files );

    for( int i = 0; i < files.count(); i++ )
        if( files[ i ].isDir() )
            Search( files[ i ].dir(), listMasks );
        else
            qDebug() << files[ i ].fileName();
}

void FileSearcher::SearchFunc( const QDir& strPath, const QStringList& setMasks, boost::condition_variable* pvarStarted )
{
    sleep( 2 );
    pvarStarted->notify_all();
    Search( strPath, setMasks );
}

void FileSearcher::StopSearch()
{
    if( m_ptrSearchThread.get() )
    {
        m_ptrSearchThread->interrupt();
        m_ptrSearchThread->join();
    }
}

void FileSearcher::StartSearch( const QDir& strPath, const QStringList& setMasks )
{
    StopSearch();
    
    boost::mutex mutStart;
    boost::unique_lock<boost::mutex> lock( mutStart );
    boost::condition_variable varStart;
    
    boost::function0< void > threadFunc = boost::bind( &FileSearcher::SearchFunc, this, strPath, 
            setMasks, &varStart );
    m_ptrSearchThread = ThreadPtr_t( new boost::thread( threadFunc ) );
    varStart.wait( lock );
    m_ptrSearchThread->join();
}

const QString FileSearcher::GetNextFinded()
{
    return "";
}

FileSearcher::~FileSearcher()
{
    StopSearch();
}

