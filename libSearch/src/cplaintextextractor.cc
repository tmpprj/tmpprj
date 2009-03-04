#include "cplaintextextractor.h"

CPlainTextExtractor::CPlainTextExtractor()
{
}

 boost::signal1< void, const std::string& >& CPlainTextExtractor::SigDataObtained()
 {
     return m_sigDataObtained;
 }
