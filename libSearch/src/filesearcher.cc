#include "filesearcher.h"
#include <globwrap.h>

using namespace std;

void CFileSearcher::Search( const std::string& strPath, const Masks_t& vMasks )
{
    for( size_t i = 0; i < vMasks.size(); i++ )
    {
        GlobWrap globFiles( strPath, vMasks[ i ] );

        const char* szFilename;
        while( ( szFilename = globFiles.NextFilename() ) != NULL )
        {
            boost::this_thread::interruption_point();
            m_sigFileProcessed( szFilename );
        }
    }

    GlobWrap globFolders( strPath );
    const char* szFilename;
    while( ( szFilename = globFolders.NextFilename() ) != NULL )
    {
        boost::this_thread::interruption_point();
        Search( szFilename, vMasks );
    }
}

void CFileSearcher::ThreadFunc( const std::string& strPath, const Masks_t& vMasks, boost::condition_variable* pvarStarted )
{
    pvarStarted->notify_all();
    Search( strPath, vMasks );
}

void CFileSearcher::StartSearch( const std::string& strPath, const Masks_t& vMasks )
{
    OnStop();
    
    boost::mutex mutStart;
    boost::unique_lock<boost::mutex> lock( mutStart );
    boost::condition_variable varStart;
    
    boost::function0< void > threadFunc = boost::bind( &CFileSearcher::ThreadFunc, this, strPath, vMasks, &varStart );
    m_ptrSearchThread = ThreadPtr_t( new boost::thread( threadFunc ) );
    varStart.wait( lock );
}

void CFileSearcher::OnStop()
{
    if( m_ptrSearchThread.get() )
    {
        m_ptrSearchThread->interrupt();
        m_ptrSearchThread->join();
    }
}

boost::signal1< void, const std::string& >& CFileSearcher::SigFileProcessed()
{
    return m_sigFileProcessed;
}

CFileSearcher::~CFileSearcher()
{
    OnStop();
}

