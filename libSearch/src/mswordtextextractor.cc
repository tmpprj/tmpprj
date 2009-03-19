#include "mswordtextextractor.h"
#include "mswordextractor.h"

CMsWordTextExtractor::CMsWordTextExtractor()
{
}

void WriterF( unsigned short int* str )
{
}

void CMsWordTextExtractor::Extract( const std::string strFileName, QString& strText )
{

    Extract( WriterF, strFileName );
}

