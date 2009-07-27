#include <fstream>
#include <QTextCodec>
#include <QFile>
#include <boost/thread.hpp>

#include "txttextextractor.h"
#include "charsetdetector.h"
#include "search_conf.h"
#include "log.hpp"

bool CTxtTextExtractor::DetectCharset( const char* pData, size_t nSize, bool& bCharsetDetected )
{
    CCharsetDetector CharDet;

    boost::this_thread::interruption_point();

    CharDet.HandleData( pData, nSize );
    CharDet.DataEnd();

    std::string strCharset = CharDet.GetCharset();
    CLog( debug ) << "Charset detected: " << strCharset;

    if( strCharset.empty() || NULL == ( m_pTextCodec = QTextCodec::codecForName( strCharset.c_str() ) ) )
        m_pTextCodec = QTextCodec::codecForLocale();
    else
        bCharsetDetected = true;

    if( NULL == m_pTextCodec )
    {
        CLog( error ) << "Cant get codec";
        return false;
    }

    return true;
}

void CTxtTextExtractor::Extract( const QString& strFileName, size_t stChunkSize )
{
    std::string strLine;
    m_pFile = boost::shared_ptr<QFile>( new QFile(strFileName) );
    if( !m_pFile->open(QIODevice::ReadOnly) )
        return;

    std::vector< char > vChunk( stChunkSize );
    bool bFirstRead = true;

    long long llTotalBytesRead = 0;
    long long llFileSize = m_pFile->size();
    bool bCharsetDetected = false;
    while( !m_pFile->atEnd() )
    {
        boost::this_thread::interruption_point();
        size_t stBytesRead = m_pFile->read( (char*)&vChunk[0], vChunk.size() );
        llTotalBytesRead += stBytesRead;
        
        //if file has grown
        if( llTotalBytesRead > llFileSize )
            break;

        if( bFirstRead )
        {
            if( !DetectCharset( &vChunk[ 0 ], stBytesRead, bCharsetDetected ) )
                break;
            bFirstRead = false;
        }

        bool bContinueSearch = true;

        if( bCharsetDetected )
        {
            CLog( debug ) << "Call SigChunk";
            QString strChunk = m_pTextCodec->toUnicode( QByteArray( (const char*)&vChunk[0], stBytesRead ) );
            bContinueSearch = !*SigChunk()( strChunk );
        }
        else
        {
            CLog( debug ) << "Call SigChunkIsRaw";
            QByteArray array( ( const char* )&vChunk[ 0 ], stBytesRead );
            bContinueSearch = !*SigChunkIsRaw()( array );
        }

        if( !bContinueSearch )
        {
            CLog( debug ) << "STOP Searching";
            break;
        }
    }
}

