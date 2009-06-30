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
            if( listFiles[ i ].isDir() )
            {
                if( listFiles[ i ].fileName() != "." && listFiles[ i ].fileName() != ".." )
                    Search( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ), listMasks );
            }
            else
            {
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


boost::signals2::signal1< void, const QString& >& CFileSearcher::SigFileFound()
{
    return m_sigFileFound;
}


