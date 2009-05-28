#include "filesearcher.h"
#include <globwrap.h>
#include <iostream>

using namespace std;

void CFileSearcher::Search( const std::string& strPath, const Masks_t& vMasks )
{
    for( size_t i = 0; i < vMasks.size(); i++ )
    {
        GlobWrap globFiles( strPath, vMasks[ i ] );

        std::string strFilename;
        while( !( strFilename = globFiles.NextFilename() ).empty() )
        {
            boost::this_thread::interruption_point();
            m_sigFileProcessed( strFilename );
        }
    }

    GlobWrap globFolders( strPath );
    std::string strFilename;
    while( !( strFilename = globFolders.NextFilename() ).empty() )
    {
        boost::this_thread::interruption_point();
        Search( strFilename, vMasks );
    }
}

void CFileSearcher::ThreadFunc( const std::string& strPath, const Masks_t& vMasks, boost::mutex* pmtxThreadStarted )
{
    cout << "StartSearch #2" << endl;
    pmtxThreadStarted->unlock();
    Search( strPath, vMasks );
}

void CFileSearcher::StartSearch( const std::string& strPath, const Masks_t& vMasks )
{
    OnStop();
    
    boost::mutex mtxThreadStarted;
    mtxThreadStarted.lock();
    
    boost::function0< void > threadFunc = boost::bind( &CFileSearcher::ThreadFunc, this, 
            strPath, vMasks, &mtxThreadStarted );
    m_ptrSearchThread = ThreadPtr_t( new boost::thread( threadFunc ) );
    
    mtxThreadStarted.lock();
    mtxThreadStarted.unlock();
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

