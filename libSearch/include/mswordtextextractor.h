#ifndef CMSWORDTEXTEXTRACTOR_H
#define CMSWORDTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CMsWordTextExtractor: public ITextExtractor
{
public:

    CMsWordTextExtractor();

    virtual void Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options );

protected:

    bool WriterFunc( QString& strBuf, unsigned short* data, size_t stChunkSize );
};

class CXlsTextExtractor: public CMsWordTextExtractor
{
public:

    CXlsTextExtractor();

    virtual void Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options );

};

class CPptTextExtractor: public CMsWordTextExtractor
{
public:

    CPptTextExtractor();

    virtual void Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options );

};
#endif // CMSWORDTEXTEXTRACTOR_H
