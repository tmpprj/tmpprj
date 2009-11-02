#include "filesearcher.h"

#include <log.h>
#include <iostream>
#include <QDir>
#include <QThread>

using namespace std;

CFileSearcher::CFileSearcher()
: CDataHandler< FileSearcher::structParams >( 2 )
{
}

void CFileSearcher::Search( const QString& strPath, const QStringList& listMasks, bool bRecursive, size_t stMinFileSize, size_t stMaxFileSize, bool bSigDone )
{
    QDir dirFiles( strPath, "", QDir::Unsorted );
    QFileInfoList listFiles = dirFiles.entryInfoList( listMasks,
		QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot );

    for (int i = 0; i < listFiles.size(); ++i)
    {
        boost::this_thread::interruption_point();

		if( listFiles[ i ].isDir() && !listFiles[ i ].isSymLink() )
        {
            if( bRecursive )
                Search( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ), listMasks, bRecursive, stMinFileSize, stMaxFileSize, false );
        }
        else if( 0 != stMaxFileSize && ( listFiles[ i ].size() > stMaxFileSize*1024 || listFiles[ i ].size() < stMinFileSize*1024 ) )
        {
            CLog(Debug) << "CFileSearcher::Search: file " << qPrintable( listFiles[i].fileName() ) << " is filtered by size: " << listFiles[ i ].size() << " bytes";
            continue;
        }
		else if( listFiles[ i ].isSymLink() )
		{
			for( size_t j = 0; j < m_Filters.size(); j++ )
				if( m_Filters[ j ].exactMatch( listFiles[ i ].fileName() ) )
				{
					m_sigFileFound( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ) );
					break;
				}
		}
		else
        {
            m_sigFileFound( dirFiles.absoluteFilePath( listFiles[ i ].fileName() ) );
        }
    }

    if( bSigDone )
        m_sigDone();
}

void CFileSearcher::WorkerFunc( const FileSearcher::structParams& Params )
{
	m_Filters.clear();
	for( int i = 0; i < Params.listMasks.size(); i++ )
		m_Filters.push_back( QRegExp( Params.listMasks[ i ], Qt::CaseInsensitive, QRegExp::Wildcard ) );

	Search( Params.strPath, Params.listMasks, Params.bRecursive, Params.stMinFileSize, Params.stMaxFileSize, true );
}


void CFileSearcher::StartSearch( const QString& strPath, const QStringList& listMasks, bool bRecursive, size_t stMinFileSize, size_t stMaxFileSize )
{
    FileSearcher::structParams Params = { strPath, listMasks, bRecursive, stMinFileSize, stMaxFileSize };
    OnData( Params );
}

boost::signals2::signal0< void >& CFileSearcher::SigDone()
{
    return m_sigDone;
}

boost::signals2::signal1< void, const QString& >& CFileSearcher::SigFileFound()
{
    return m_sigFileFound;
}


