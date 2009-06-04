#ifndef CMSWORDTEXTEXTRACTOR_H
#define CMSWORDTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CMsWordTextExtractor: public ITextExtractor
{
public:

    CMsWordTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText );

protected:

    void WriterFunc( QString& strBuf, unsigned short* data );

};

class CXlsTextExtractor: public CMsWordTextExtractor
{
public:

    CXlsTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText );

};

class CPptTextExtractor: public CMsWordTextExtractor
{
public:

    CPptTextExtractor();

    virtual void Extract( const QString& strFileName, QString& strText );

};
#endif // CMSWORDTEXTEXTRACTOR_H
