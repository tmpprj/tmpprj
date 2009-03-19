#ifndef CTXTTEXTEXTRACTOR_H
#define CTXTTEXTEXTRACTOR_H

#include "plaintextextractor.h"
#include <string>

class CTxtTextExtractor: public ITextExtractor
{
public:

    CTxtTextExtractor();

    virtual void Extract( const std::string strFileName, QString& strText );

private:


};

#endif // CTXTTEXTEXTRACTOR_H
