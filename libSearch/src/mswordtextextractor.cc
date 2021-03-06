#include "mswordtextextractor.h"
#include "mswordextractor.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/concept_check.hpp>
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
            if( !*SigChunk()( strBuf ) )
                return false;
            strBuf.clear();
        }
    }
    return true;
}

void CMsWordTextExtractor::Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options )
{
    boost::ignore_unused_variable_warning( options );
    QString strBuf;
    MsWord::Extract( boost::bind( &CMsWordTextExtractor::WriterFunc, this, boost::ref( strBuf ), _1, stChunkSize ), strFileName );
    SigChunk()( strBuf );
}

CXlsTextExtractor::CXlsTextExtractor()
{
    m_strName = "Microsoft Excel Spreadsheet Parser";
}

void CXlsTextExtractor::Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options )
{
    boost::ignore_unused_variable_warning( options );
    QString strBuf;
    MsWord::ExtractXls( boost::bind( &CXlsTextExtractor::WriterFunc, this, boost::ref( strBuf ), _1, stChunkSize ), strFileName );
    SigChunk()( strBuf );
}

CPptTextExtractor::CPptTextExtractor()
{
    m_strName = "Microsoft PowerPoint Document Parser";
}

void CPptTextExtractor::Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options )
{
    boost::ignore_unused_variable_warning( options );
    QString strBuf;
    MsWord::ExtractPpt( boost::bind( &CPptTextExtractor::WriterFunc, this, boost::ref( strBuf ), _1, stChunkSize ), strFileName );
    SigChunk()( strBuf );
}
