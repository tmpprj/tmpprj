#include "txttextextractor.h"
#include "charsetdetector.h"
#include <fstream>
#include <QTextCodec>
#include "log.hpp"


void CTxtTextExtractor::Extract( const QString& strFileName, QString& strText )
{
    std::string strLine;
    std::ifstream file( strFileName.toStdString().c_str(), std::ios::in|std::ios::binary|std::ios::ate );

    CCharsetDetector CharDet;
    std::vector<unsigned char> vecBuf;

    if (file.is_open())
    {
//TODO: add interruption point
        size_t stFileSize = file.tellg();
        vecBuf.resize( stFileSize );
        file.seekg( 0, std::ios::beg );
        file.read( (char*)&vecBuf[0], stFileSize );
        file.close();
    }
    //TODO:maybe it`s faster to handle data blocks of some size, 1024 bytes for example
    CharDet.HandleData( (char*)&vecBuf[0], vecBuf.size() );
    CharDet.DataEnd();

    std::string strCharset = CharDet.GetCharset();

    QTextCodec* pTextCodec = strCharset.empty() ? QTextCodec::codecForLocale() : QTextCodec::codecForName( strCharset.c_str() );
    if( NULL == pTextCodec )
    {
        CLog() << debug << "Cant get codec" << std::endl;
        strText.fromAscii( (const char*)&vecBuf[0], vecBuf.size() );
    }
    else
    {
        strText = pTextCodec->toUnicode( QByteArray( (const char*)&vecBuf[0], vecBuf.size() ) );
    }
}
