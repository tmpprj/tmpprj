#ifndef PDFTEXTEXTRACTOR_H
#define PDFTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CPdfTextExtractor: public ITextExtractor
{
public:

    CPdfTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText );

protected:

    void WriterFunc( QString& strBuf, unsigned int* data, size_t stSize );

};
#endif // PDFTEXTEXTRACTOR_H
