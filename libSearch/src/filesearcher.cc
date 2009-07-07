#include "filesearcher.h"

#include <log.hpp>
#include <globwrap.h>
#include <iostream>
#include <QDir>
#include <QThread>

using namespace std;

CFileSearcher::CFileSearcher()
: CDataHandler< FileSearcher::structParams >( 2 )
{
}

void CFileSearcher::Search( const QString& strPath, const QStringList& listMasks, bool bRecursive )
{
    {
        QDir dirFiles( strPath, "", QDir::Unsorted );
        QFileInfoList listFiles = dirFiles.entryInfoList( listMasks, 
                QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot );

        for (int i = 0; i < listFiles.size(); ++i)
        {
            boost::this_thread::interruption_point();
            if( listFiles[ i ].isDir() )
            {
                if( bRecursive )
                    Search( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ), listMasks, bRecursive );
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
    Search( Params.strPath, Params.listMasks, Params.bRecursive );
}


void CFileSearcher::StartSearch( const QString& strPath, const QStringList& listMasks, bool bRecursive )
{
    FileSearcher::structParams Params = { strPath, listMasks, bRecursive };
    OnData( Params );
}


boost::signals2::signal1< void, const QString& >& CFileSearcher::SigFileFound()
{
    return m_sigFileFound;
}


