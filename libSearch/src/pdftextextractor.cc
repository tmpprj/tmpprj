#include "include\pdftextextractor.h"
#include "pdfextractor.h"
#include <boost/bind.hpp>

CPdfTextExtractor::CPdfTextExtractor()
{
}

void CPdfTextExtractor::WriterFunc( QString& strBuf, unsigned int* data, size_t stSize )
{
    for( size_t i = 0; i < stSize; ++i )
        strBuf += QChar( data[i] );
}

void CPdfTextExtractor::Extract( const std::string strFileName, QString& strText )
{
    Pdf::Extract( boost::bind( &CPdfTextExtractor::WriterFunc, this, boost::ref(strText), _1, _2 ), strFileName );
}
