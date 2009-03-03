#include "filesearcher.h"
#include <glob.h>

using namespace std;

void FileSearcher::Search( const std::string& strPath, const Masks_t& vMasks )
{
    for( size_t i = 0; i < vMasks.size(); i++ )
    {
        glob_t gt;
        glob( ( strPath + "/" + vMasks[ i ] ).c_str(), GLOB_NOSORT, NULL, &gt );

        for( size_t i = 0; i < gt.gl_pathc; i++ )
        {
            boost::this_thread::interruption_point();
            m_sigFileProcessed( gt.gl_pathv[ i ] );
        }

        globfree( &gt );
    }

    glob_t gtDir;
    glob( ( strPath + "/*" ).c_str(), GLOB_ONLYDIR, NULL, &gtDir );

    for( size_t i = 0; i < gtDir.gl_pathc; i++ )
        Search( gtDir.gl_pathv[ i ], vMasks );

    globfree( &gtDir );
}

void FileSearcher::SearchFunc( const std::string& strPath, const Masks_t& vMasks, boost::condition_variable* pvarStarted )
{
    pvarStarted->notify_all();
    Search( strPath, vMasks );
}

void FileSearcher::StartSearch( const std::string& strPath, const Masks_t& vMasks )
{
    StopSearch();
    
    boost::mutex mutStart;
    boost::unique_lock<boost::mutex> lock( mutStart );
    boost::condition_variable varStart;
    
    boost::function0< void > threadFunc = boost::bind( &FileSearcher::SearchFunc, this, strPath, vMasks, &varStart );
    m_ptrSearchThread = ThreadPtr_t( new boost::thread( threadFunc ) );
    varStart.wait( lock );
    m_ptrSearchThread->join();
}

void FileSearcher::StopSearch()
{
    if( m_ptrSearchThread.get() )
    {
        m_ptrSearchThread->interrupt();
        m_ptrSearchThread->join();
    }
}

boost::signal1< void, const std::string& >& FileSearcher::SigFileProcessed()
{
    return m_sigFileProcessed;
}

FileSearcher::~FileSearcher()
{
    StopSearch();
}

