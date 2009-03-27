#include "mswordtextextractor.h"
#include "mswordextractor.h"
#include <boost/bind.hpp>
#include <QtDebug>
#include <QTextCodec>

CMsWordTextExtractor::CMsWordTextExtractor()
{
}

void CMsWordTextExtractor::WriterFunc( QString& strBuf, unsigned short* data )
{
    while( *data )
    {
        strBuf += QChar( *data );
        qDebug() << "+letter:" << QChar( *data ) << " plain: " << *data;
        data++;
    }
}

void CMsWordTextExtractor::Extract( const std::string strFileName, QString& strText )
{
    MsWord::Extract( boost::bind( &CMsWordTextExtractor::WriterFunc, this, boost::ref(strText), _1 ), strFileName );
}

CXlsTextExtractor::CXlsTextExtractor()
{
}

void CXlsTextExtractor::Extract( const std::string strFileName, QString& strText )
{
    MsWord::ExtractXls( boost::bind( &CXlsTextExtractor::WriterFunc, this, boost::ref(strText), _1 ), strFileName );
}
