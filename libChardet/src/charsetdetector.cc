#include "charsetdetector.h"

CCharsetDetector::CCharsetDetector():nsUniversalDetector(NS_FILTER_ALL)
{};

CCharsetDetector::~CCharsetDetector()
{};

bool CCharsetDetector::Done() const
{
    return 0 != mDone;
}

std::string CCharsetDetector::GetCharset()
{
    return m_strCharset;
}

void CCharsetDetector::Report(const char* aCharset)
{
    m_strCharset = aCharset;
};

