#include "pdftextextractor.h"
#include "pdfextractor.h"
#include <boost/bind.hpp>

CPdfTextExtractor::CPdfTextExtractor()
{
    m_strName = "Portable Document Format Parser";
}

bool CPdfTextExtractor::WriterFunc( QString& strBuf, unsigned int* data, size_t stSize, size_t stChunkSize )
{
    for( size_t i = 0; i < stSize; ++i )
    {
        if( (size_t)strBuf.size() >= stChunkSize )
        {
            if( !SigChunk()( strBuf ) )
                return false;
            strBuf.clear();
        }

        strBuf += QChar( data[i] );
    }

    return true;
}

void CPdfTextExtractor::Extract( const QString& strFileName, size_t stChunkSize )
{
    Pdf::Extract( boost::bind( &CPdfTextExtractor::WriterFunc, this, boost::ref(m_strBuf), _1, _2, stChunkSize ), strFileName );
    SigChunk()( m_strBuf );
}
