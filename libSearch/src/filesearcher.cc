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
            if( strFilename[ strFilename.size() - 1 ] != '/' )
                m_sigFileProcessed( QString::fromStdString(strFilename) );
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

void CFileSearcher::WorkerFunc( const FileSearcher::structParams& Params )
{
    Search( Params.strPath, Params.vMasks );
}


void CFileSearcher::StartSearch( const std::string& strPath, const Masks_t& vMasks )
{
    FileSearcher::structParams Params = { strPath, vMasks };
    OnData( Params );
}


boost::signal1< void, const QString& >& CFileSearcher::SigFileProcessed()
{
    return m_sigFileProcessed;
}


