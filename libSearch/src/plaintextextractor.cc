#include "txttextextractor.h"
#include "plaintextextractor.h"
#include "mswordtextextractor.h"
#include "pdftextextractor.h"
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
    : m_pDefaultExtractor( NULL )
{
    RegisterName( "TextParser", new CTxtTextExtractor );
    RegisterName( "DocParser", new CMsWordTextExtractor );
    RegisterName( "XlsParser", new CXlsTextExtractor );
    RegisterName( "PptParser", new CPptTextExtractor );
    RegisterName( "PdfParser", new CPdfTextExtractor );

    m_pDefaultExtractor = mapNameExtractors[ "TextParser" ];
}

CTextExtractorFactory::~CTextExtractorFactory()
{
    BOOST_FOREACH( MapNameExtractors_t::value_type& p, mapNameExtractors )
        delete p.second;
}

ITextExtractor* CTextExtractorFactory::GetExtractor( const std::string& strFileName )
{
    boost::filesystem::path file( strFileName );
    
    MapExtensionName_t::iterator pName = mapExtensionName.find( file.extension() );
    if( pName == mapExtensionName.end() )
        return m_pDefaultExtractor;
    
    MapNameExtractors_t::iterator pExtractor = mapNameExtractors.find( pName->second );
    if( pExtractor == mapNameExtractors.end() )
        return m_pDefaultExtractor;

    return pExtractor->second;
}

bool CTextExtractorFactory::RegisterName( const std::string& strName, ITextExtractor* pTextExtractor )
{
    if( mapNameExtractors.count( strName ) == 0 )
    {
        mapNameExtractors[ strName ] = pTextExtractor;
        return true;
    }
    return false;
}

bool CTextExtractorFactory::RegisterExtension( const std::string& strExt, const std::string& strName )
{
    if( mapNameExtractors.count( strName ) > 0 )
    {
        mapExtensionName[ strExt ] = strName; 
        return true;
    }
    return false;
}

