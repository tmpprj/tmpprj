#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

class CPlainTextExtractor
{
public:

    CPlainTextExtractor();

    boost::signal1< void, const std::string& >& SigDataObtained();

private:

    enum enumEvents
    {
        EV_FILEAVAIL,
        EV_STOP
    };

    void ReleaseWait( int iAction

    void OnSignal( const std::string& strFileName );

    boost::signal1< void, const std::string& > m_sigDataObtained;
};

#endif // CPLAINTEXTEXTRACTOR_H
