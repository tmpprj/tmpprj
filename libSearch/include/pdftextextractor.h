#ifndef PDFTEXTEXTRACTOR_H
#define PDFTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CPdfTextExtractor: public ITextExtractor
{
public:

    CPdfTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText, size_t stChunkSize );

protected:

    bool WriterFunc( QString& strBuf, unsigned int* data, size_t stSize, size_t stChunkSize );

};
#endif // PDFTEXTEXTRACTOR_H
