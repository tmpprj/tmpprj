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
            {
                CLog() << "Call found" << std::endl;
                m_sigFileFound( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ) );
            }
        }
    }
}

void CFileSearcher::WorkerFunc( const FileSearcher::structParams& Params )
{
    Search( Params.strPath, Params.listMasks );
}


void CFileSearcher::StartSearch( const QString& strPath, const QStringList& listMasks )
{
    FileSearcher::structParams Params = { strPath, listMasks };
    OnData( Params );
}


boost::signal1< void, const QString& >& CFileSearcher::SigFileFound()
{
    return m_sigFileFound;
}


