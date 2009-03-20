#ifndef CMSWORDTEXTEXTRACTOR_H
#define CMSWORDTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CMsWordTextExtractor: public ITextExtractor
{
public:

    CMsWordTextExtractor();

    virtual void Extract( const std::string strFileName, QString& strText );

private:

    void WriterFunc( QString& strBuf, unsigned short* data );

};

#endif // CMSWORDTEXTEXTRACTOR_H
