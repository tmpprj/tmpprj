#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

#include <string>

class CPlainTextExtractor
{
public:

    CPlainTextExtractor();

    boost::signal1< void, const std::string& >& SigDataObtained();

    void OnNewFile( const std::string& strFileName );

    void OnStop();

private:

    boost::signal1< void, const std::string& > m_sigDataObtained;
};

#endif // CPLAINTEXTEXTRACTOR_H
