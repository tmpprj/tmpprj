#include "txttextextractor.h"
#include "plaintextextractor.h"
#include "mswordtextextractor.h"
#include "log.hpp"
#include <boost/foreach.hpp>

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
    RegisterExtractor( ".doc", new CMsWordTextExtractor );
    RegisterExtractor( ".rtf", new CMsWordTextExtractor );
    RegisterExtractor( ".xls", new CXlsTextExtractor );
    RegisterExtractor( ".ppt", new CPptTextExtractor );
}

CTextExtractorFactory::~CTextExtractorFactory()
{
    typedef std::pair<const std::string, ITextExtractor*>& pair_t_ref;
    BOOST_FOREACH( pair_t_ref p, mapExtractors )
            delete p.second;
}

ITextExtractor* CTextExtractorFactory::GetExtractor( const std::string& strFileName )
{
    boost::filesystem::path file( strFileName );
    if( mapExtractors.end() == mapExtractors.find( file.extension() ) )
        return mapExtractors[ ".txt" ];
    else
        return mapExtractors[ file.extension() ];
}

bool CTextExtractorFactory::RegisterExtractor( const std::string& strFormat, ITextExtractor* pTextExtractor )
{
    mapExtractors[ strFormat ] = pTextExtractor;
    return true;
}
