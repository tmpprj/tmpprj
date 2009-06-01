#include "mswordtextextractor.h"
#include "mswordextractor.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <QTextCodec>


CMsWordTextExtractor::CMsWordTextExtractor()
{
}

void CMsWordTextExtractor::WriterFunc( QString& strBuf, unsigned short* data )
{
    unsigned short* start = data;
    while( *data )
    {
        strBuf += QChar( *data );
        data++;

        if( (data - start)%100 == 0 )
            boost::this_thread::interruption_point();
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

CPptTextExtractor::CPptTextExtractor()
{
}

void CPptTextExtractor::Extract( const std::string strFileName, QString& strText )
{
    MsWord::ExtractPpt( boost::bind( &CPptTextExtractor::WriterFunc, this, boost::ref(strText), _1 ), strFileName );
}
