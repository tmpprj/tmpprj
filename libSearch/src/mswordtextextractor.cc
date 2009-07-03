#include "mswordtextextractor.h"
#include "mswordextractor.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <QTextCodec>


CMsWordTextExtractor::CMsWordTextExtractor()
{
    m_strName = "Microsoft Word Document Parser";
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

void CMsWordTextExtractor::Extract( const QString& strFileName, QString& strText )
{
    MsWord::Extract( boost::bind( &CMsWordTextExtractor::WriterFunc, this, boost::ref(strText), _1 ), strFileName );
}

CXlsTextExtractor::CXlsTextExtractor()
{
    m_strName = "Microsoft Excel Spreadsheet Parser";
}

void CXlsTextExtractor::Extract( const QString& strFileName, QString& strText )
{
    MsWord::ExtractXls( boost::bind( &CXlsTextExtractor::WriterFunc, this, boost::ref(strText), _1 ), strFileName );
}

CPptTextExtractor::CPptTextExtractor()
{
    m_strName = "Microsoft PowerPoint Document Parser";
}

void CPptTextExtractor::Extract( const QString& strFileName, QString& strText )
{
    MsWord::ExtractPpt( boost::bind( &CPptTextExtractor::WriterFunc, this, boost::ref(strText), _1 ), strFileName );
}
