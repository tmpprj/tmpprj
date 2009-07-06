#include <fstream>
#include <QTextCodec>
#include <QFile>
#include <boost/thread.hpp>

#include "txttextextractor.h"
#include "charsetdetector.h"
#include "search_conf.h"
#include "log.hpp"

bool CTxtTextExtractor::DetectCharset( const char* pData, size_t nSize )
{
    CCharsetDetector CharDet;

    boost::this_thread::interruption_point();

    CharDet.HandleData( pData, nSize );
    CharDet.DataEnd();

    std::string strCharset = CharDet.GetCharset();
    CLog( debug ) << "Charset detected: " << strCharset;

    if( strCharset.empty() || NULL == ( m_pTextCodec = QTextCodec::codecForName( strCharset.c_str() ) ) )
        m_pTextCodec = QTextCodec::codecForLocale();

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

    while( !m_pFile->atEnd() )
    {
        boost::this_thread::interruption_point();
        size_t stBytesRead = m_pFile->read( (char*)&vChunk[0], vChunk.size() );

        if( bFirstRead )
        {
            if( !DetectCharset( &vChunk[ 0 ], stBytesRead ) )
                return;
            bFirstRead = false;
        }

        QString strChunk = m_pTextCodec->toUnicode( QByteArray( (const char*)&vChunk[0], stBytesRead ) );
        if( !*SigChunk()( strChunk ) )
        {
            CLog( debug ) << "STOP Searching";
            break;
        }
    }
}

