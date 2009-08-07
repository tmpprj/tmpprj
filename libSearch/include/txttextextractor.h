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
        m_strName = "Plain Text Document Parser";
    }

    virtual void Extract( const QString& strFileName, size_t stChunkSize, const SearchOptions& options );

private:

    bool DetectCharset( const char* pData, size_t nSize, bool& bCharsetDetected );

    boost::shared_ptr<QFile> m_pFile;

    QTextCodec* m_pTextCodec;
};

#endif // CTXTTEXTEXTRACTOR_H
