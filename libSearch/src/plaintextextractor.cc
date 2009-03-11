#include "plaintextextractor.h"

CPlainTextExtractor::CPlainTextExtractor()
{
}

boost::signal1< void, const QString& >& CPlainTextExtractor::SigDataObtained()
{
    return m_sigDataObtained;
}

void CPlainTextExtractor::ThreadFunc( boost::mutex* pmtxThreadStarted )
{
    pmtxThreadStarted->unlock();
    std::string strFileName = m_Queue.pop();

    boost::this_thread::interruption_point();

    //Process file
    QString strContent;
    TextExtractorFactory::Instance().GetExtractor( strFileName )->Extract( strFileName, strContent );
    m_sigDataObtained( strContent );
}
