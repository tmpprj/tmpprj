#include "txttextextractor.h"
#include "plaintextextractor.h"

CPlainTextExtractor::CPlainTextExtractor()
{
}

boost::signal2< void, const std::string&, const QString& >& CPlainTextExtractor::SigDataObtained()
{
    return m_sigDataObtained;
}

void CPlainTextExtractor::ThreadFunc( boost::mutex* pmtxThreadStarted )
{
    pmtxThreadStarted->unlock();

    for(;;)
    {
        std::string strFileName = m_Queue.pop();

        boost::this_thread::interruption_point();

        //Process file
        QString strContent;
        TextExtractorFactory::Instance().GetExtractor( strFileName )->Extract( strFileName, strContent );
        m_sigDataObtained( strFileName, strContent );
    }
}

CTextExtractorFactory::CTextExtractorFactory()
{
    RegisterExtractor( ".txt", new CTxtTextExtractor );
}
