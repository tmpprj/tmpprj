#ifndef CTXTTEXTEXTRACTOR_H
#define CTXTTEXTEXTRACTOR_H

#include "plaintextextractor.h"
#include <QString>

class QFile;

class CTxtTextExtractor: public ITextExtractor
{
public:

    CTxtTextExtractor():m_pTextCodec(NULL)
    {
        m_strName = "TXT Parser";
    }

    virtual void Extract( const QString& strFileName, QString& strText, size_t stChunkSize );

private:

    boost::shared_ptr<QFile> m_pFile;

    QTextCodec* m_pTextCodec;

    std::vector<unsigned char> m_vecBuf;
};

#endif // CTXTTEXTEXTRACTOR_H
