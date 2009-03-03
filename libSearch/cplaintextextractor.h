#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

class CPlainTextExtractor
{
public:

    CPlainTextExtractor();

    boost::signal1< void, const std::string& >& SigDataObtained();
};

#endif // CPLAINTEXTEXTRACTOR_H
