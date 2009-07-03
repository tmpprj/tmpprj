#include <fstream>
#include <QTextCodec>
#include <QFile>
#include <boost/thread.hpp>

#include "txttextextractor.h"
#include "charsetdetector.h"
#include "search_conf.h"
#include "log.hpp"

void CTxtTextExtractor::Extract( const QString& strFileName, size_t stChunkSize )
{
    std::string strLine;
    m_pFile = boost::shared_ptr<QFile>( new QFile(strFileName) );
    if( !m_pFile->open(QIODevice::ReadOnly) )
        return;

    CCharsetDetector CharDet;
    size_t stBlockSize = SearchConf().stCharDetBlockSize.Value();
    m_vecBuf.resize( stChunkSize < stBlockSize ? stChunkSize : stBlockSize );

    size_t stBytesRead = 0;
    stBytesRead = m_pFile->read( (char*)&m_vecBuf[0], m_vecBuf.size() );

    boost::this_thread::interruption_point();

    CharDet.HandleData( (char*)&m_vecBuf[0], stBytesRead );
    CharDet.DataEnd();

    std::string strCharset = CharDet.GetCharset();

    if( strCharset.empty() || NULL == ( m_pTextCodec = QTextCodec::codecForName( strCharset.c_str() ) ) )
        m_pTextCodec = QTextCodec::codecForLocale();

    if( NULL == m_pTextCodec )
    {
        CLog(debug) << "Cant get codec";
        return;
    }

    QString strBuf;
    strBuf += m_pTextCodec->toUnicode( QByteArray( (const char*)&m_vecBuf[0], stBytesRead ) );

    if( m_vecBuf.size() < stChunkSize )
        m_vecBuf.resize( stChunkSize );

    while( m_pFile->atEnd() )
    {
        size_t stBytesRead = m_pFile->read( (char*)&m_vecBuf[0], stChunkSize );
    
        strBuf += m_pTextCodec->toUnicode( QByteArray( (const char*)&m_vecBuf[0], stBytesRead ) );

        if( !SigChunk()( strBuf ) )
            break;

        strBuf.clear();
    }
}

