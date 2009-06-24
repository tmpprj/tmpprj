#include "filesearcher.h"

#include <log.hpp>
#include <globwrap.h>
#include <iostream>
#include <QDir>

using namespace std;

void CFileSearcher::Search( const QString& strPath, const QStringList& listMasks )
{
    {
        QDir dirFiles( strPath, "", QDir::Unsorted );
        QFileInfoList listFiles = dirFiles.entryInfoList( listMasks, 
                QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::System );

        for (int i = 0; i < listFiles.size(); ++i)
        {
            boost::this_thread::interruption_point();
            CLog() << "Search: " << qPrintable( listFiles[ i ].fileName() ) << std::endl;
            if( listFiles[ i ].isDir() )
            {
                if( listFiles[ i ].fileName() != "." && listFiles[ i ].fileName() != ".." )
                    Search( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ), listMasks );
            }
            else
                m_sigFileFound( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ) );
        }
    }

//        GlobWrap globFiles( strPath, vMasks[ i ] );
//
//        std::string strFilename;
//        while( !( strFilename = globFiles.NextFilename() ).empty() )
//        {
//            boost::this_thread::interruption_point();
//            if( strFilename[ strFilename.size() - 1 ] != '/' )
//                m_sigFileProcessed( QString::fromStdString(strFilename) );
//        }
//    }
//
//    GlobWrap globFolders( strPath );
//    std::string strFilename;
//    while( !( strFilename = globFolders.NextFilename() ).empty() )
//    {
//        boost::this_thread::interruption_point();
//        Search( strFilename, vMasks );
//    }
}

void CFileSearcher::WorkerFunc( const FileSearcher::structParams& Params )
{
    Search( Params.strPath, Params.vMasks );
}


void CFileSearcher::StartSearch( const QString& strPath, const Masks_t& vMasks )
{
    FileSearcher::structParams Params = { strPath, vMasks };
    OnData( Params );
}


boost::signal1< void, const QString& >& CFileSearcher::SigFileFound()
{
    return m_sigFileFound;
}


