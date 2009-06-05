#include "filesearcher.h"
#include <globwrap.h>
#include <iostream>
#include <QDir>

using namespace std;

void CFileSearcher::Search( const QString& strPath, const Masks_t& vMasks )
{
    QString strMask;
    for( size_t i = 0; i < vMasks.size(); i++ )
       strMask += QString::fromStdString(vMasks[i]) + ";";

    {
        QDir dirFiles( strPath, strMask, QDir::Unsorted, QDir::Files );
        QFileInfoList listFiles = dirFiles.entryInfoList();
        for (int i = 0; i < listFiles.size(); ++i)
        {
            boost::this_thread::interruption_point();
            m_sigFileProcessed( dirFiles.absoluteFilePath(listFiles.at(i).fileName()) );
        }
    }

    {
        QDir dirDirs( strPath, QString(""), QDir::Unsorted, QDir::AllDirs | QDir::NoDotAndDotDot );
        QFileInfoList listDirs= dirDirs.entryInfoList();
        for (int i = 0; i < listDirs.size(); ++i)
        {
            boost::this_thread::interruption_point();
            Search( dirDirs.absoluteFilePath(listDirs.at(i).fileName()), vMasks );
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


boost::signal1< void, const QString& >& CFileSearcher::SigFileProcessed()
{
    return m_sigFileProcessed;
}


