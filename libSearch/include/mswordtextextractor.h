#ifndef CMSWORDTEXTEXTRACTOR_H
#define CMSWORDTEXTEXTRACTOR_H

#include "plaintextextractor.h"

class CMsWordTextExtractor: public ITextExtractor
{
public:

    CMsWordTextExtractor();

    virtual void Extract( const std::string strFileName, QString& strText );

private:


};

#endif // CMSWORDTEXTEXTRACTOR_H
