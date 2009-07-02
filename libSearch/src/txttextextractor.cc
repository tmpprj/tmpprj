#include <fstream>
#include <QTextCodec>
#include <QFile>
#include <boost/thread.hpp>

#include "txttextextractor.h"
#include "charsetdetector.h"
#include "search_conf.h"
#include "log.hpp"


void CTxtTextExtractor::Extract( const QString& strFileName, QString& strText )
{
    std::string strLine;
    QFile file( strFileName );
    if( !file.open(QIODevice::ReadOnly) )
        return;

    CCharsetDetector CharDet;
    std::vector<unsigned char> vecBuf(SearchConf().stCharDetBlockSize.Value());
    size_t stBytesRead = 0;

    stBytesRead = file.read( (char*)&vecBuf[0], vecBuf.size() );
    boost::this_thread::interruption_point();
    CharDet.HandleData( (char*)&vecBuf[0], stBytesRead );
    CharDet.DataEnd();

    std::string strCharset = CharDet.GetCharset();

    QTextCodec* pTextCodec = strCharset.empty() ? QTextCodec::codecForLocale() : QTextCodec::codecForName( strCharset.c_str() );
    if( NULL == pTextCodec )
         CLog(debug) << "Cant get codec";
    else
    {
        vecBuf.resize( 1024000 );
        strText += pTextCodec->toUnicode( QByteArray( (const char*)&vecBuf[0], stBytesRead ) );
        while( !file.atEnd() )
        {
            stBytesRead = file.read( (char*)&vecBuf[0], vecBuf.size() );
            strText += pTextCodec->toUnicode( QByteArray( (const char*)&vecBuf[0], stBytesRead ) );
        }
        
    }
}
