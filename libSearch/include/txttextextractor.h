#ifndef CTXTTEXTEXTRACTOR_H
#define CTXTTEXTEXTRACTOR_H

#include "plaintextextractor.h"
#include <QString>

class CTxtTextExtractor: public ITextExtractor
{
public:

    virtual void Extract( const QString& strFileName, QString& strText );

private:


};

#endif // CTXTTEXTEXTRACTOR_H
