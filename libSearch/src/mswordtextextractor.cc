#include "mswordtextextractor.h"
#include "mswordextractor.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <QTextCodec>


CMsWordTextExtractor::CMsWordTextExtractor()
{
    m_strName = "Microsoft Word Document Parser";
}

bool CMsWordTextExtractor::WriterFunc( QString& strBuf, unsigned short* data, size_t stChunkSize )
{
    unsigned short* start = data;
    while( *data )
    {
        strBuf += QChar( *data );
        data++;

        if( (data - start)%100 == 0 )
            boost::this_thread::interruption_point();

        if( (size_t)strBuf.size() >= stChunkSize )
        {
            if( !SigChunk()( strBuf ) )
                return false;
            strBuf.clear();
        }
    }
    return true;
}

void CMsWordTextExtractor::Extract( const QString& strFileName, size_t stChunkSize )
{
    MsWord::Extract( boost::bind( &CMsWordTextExtractor::WriterFunc, this, boost::ref(m_strBuf), _1, stChunkSize ), strFileName );
    SigChunk()( m_strBuf );
}

CXlsTextExtractor::CXlsTextExtractor()
{
    m_strName = "Microsoft Excel Spreadsheet Parser";
}

void CXlsTextExtractor::Extract( const QString& strFileName, size_t stChunkSize )
{
    MsWord::ExtractXls( boost::bind( &CXlsTextExtractor::WriterFunc, this, boost::ref(m_strBuf), _1, stChunkSize ), strFileName );
    SigChunk()( m_strBuf );
}

CPptTextExtractor::CPptTextExtractor()
{
    m_strName = "Microsoft PowerPoint Document Parser";
}

void CPptTextExtractor::Extract( const QString& strFileName, size_t stChunkSize )
{
    MsWord::ExtractPpt( boost::bind( &CPptTextExtractor::WriterFunc, this, boost::ref(m_strBuf), _1, stChunkSize ), strFileName );
    SigChunk()( m_strBuf );
}
