#include "plaintextextractor.h"

CPlainTextExtractor::CPlainTextExtractor()
{
}

 boost::signal1< void, const QString& >& CPlainTextExtractor::SigDataObtained()
 {
     return m_sigDataObtained;
 }
