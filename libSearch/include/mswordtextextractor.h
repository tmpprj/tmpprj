#ifndef CMSWORDTEXTEXTRACTOR_H
#define CMSWORDTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CMsWordTextExtractor: public ITextExtractor
{
public:

    CMsWordTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText, size_t stChunkSize );

protected:

    bool WriterFunc( QString& strBuf, unsigned short* data, size_t stChunkSize );

};

class CXlsTextExtractor: public CMsWordTextExtractor
{
public:

    CXlsTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText, size_t stChunkSize );

};

class CPptTextExtractor: public CMsWordTextExtractor
{
public:

    CPptTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText, size_t stChunkSize );

};
#endif // CMSWORDTEXTEXTRACTOR_H
