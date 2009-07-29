#include "filesearcher.h"

#include <log.h>
#include <globwrap.h>
#include <iostream>
#include <QDir>
#include <QThread>

using namespace std;

CFileSearcher::CFileSearcher()
: CDataHandler< FileSearcher::structParams >( 2 )
{
}

void CFileSearcher::Search( const QString& strPath, const QStringList& listMasks, bool bRecursive, size_t stMinFileSize, size_t stMaxFileSize )
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
                    Search( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ), listMasks, bRecursive, stMinFileSize, stMaxFileSize );
            }
            else if( 0 != stMaxFileSize && ( listFiles[ i ].size() > stMaxFileSize*1024 || listFiles[ i ].size() < stMinFileSize*1024 ) )
            {
                CLog(debug) << "CFileSearcher::Search: file " << qPrintable( listFiles[i].fileName() ) << " is filtered by size: " << listFiles[ i ].size() << " bytes";
                continue;
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
    Search( Params.strPath, Params.listMasks, Params.bRecursive, Params.stMinFileSize, Params.stMaxFileSize );
}


void CFileSearcher::StartSearch( const QString& strPath, const QStringList& listMasks, bool bRecursive, size_t stMinFileSize, size_t stMaxFileSize )
{
    FileSearcher::structParams Params = { strPath, listMasks, bRecursive, stMinFileSize, stMaxFileSize };
    OnData( Params );
}


boost::signals2::signal1< void, const QString& >& CFileSearcher::SigFileFound()
{
    return m_sigFileFound;
}


