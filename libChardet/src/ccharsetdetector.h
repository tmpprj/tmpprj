#ifndef CCHARSETDETECTOR_H
#define CCHARSETDETECTOR_H

#include "src/nsUniversalDetector.h"
#include <string>


class CCharsetDetector: public nsUniversalDetector
{
public:

    CCharsetDetector();

    virtual ~CCharsetDetector();

    bool Done() const;

    std::string GetCharset();

private:

    virtual void Report(const char* aCharset);

    std::string m_strCharset;
};

#endif // CCHARSETDETECTOR_H
