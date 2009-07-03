#ifndef CTXTTEXTEXTRACTOR_H
#define CTXTTEXTEXTRACTOR_H

#include "plaintextextractor.h"
#include <QString>

class CTxtTextExtractor: public ITextExtractor
{
public:

    CTxtTextExtractor()
    {
        m_strName = "Plain Text Document Parser";
    }

    virtual void Extract( const QString& strFileName, QString& strText );

private:


};

#endif // CTXTTEXTEXTRACTOR_H
