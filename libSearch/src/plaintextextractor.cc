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
    RegisterName( "TXT Parser", new CTxtTextExtractor );
    RegisterName( "DOC Parser", new CMsWordTextExtractor );
    RegisterName( "XLS Parser", new CXlsTextExtractor );
    RegisterName( "PPT Parser", new CPptTextExtractor );
    RegisterName( "PDF Parser", new CPdfTextExtractor );

    m_pDefaultExtractor = m_mapNameExtractor[ "TXT Parser" ];
}

CTextExtractorFactory::~CTextExtractorFactory()
{
    BOOST_FOREACH( MapNameExtractor_t::value_type& p, m_mapNameExtractor )
            delete p.second;
}

ITextExtractor* CTextExtractorFactory::GetExtractor( const std::string& strFileName )
{
    boost::filesystem::path file( strFileName );

    MapExtensionName_t::iterator pExtName = m_mapExtensionName.find( file.extension() );
    if( pExtName == m_mapExtensionName.end() )
        return m_pDefaultExtractor;

    MapNameExtractor_t::iterator pNameExtractor = m_mapNameExtractor.find( pExtName->second );
    if( pNameExtractor == m_mapNameExtractor.end() )
        return m_pDefaultExtractor;
    
    return pNameExtractor->second;
}


bool CTextExtractorFactory::RegisterName( const std::string& strName, ITextExtractor* pTextExtractor )
{
    MapNameExtractor_t::iterator p = m_mapNameExtractor.find( strName );

    if( p != m_mapNameExtractor.end() )
        return false;
    
    m_mapNameExtractor[ strName ] = pTextExtractor;
    return true;
}

bool CTextExtractorFactory::RegisterExtension( const std::string& strExtension, const std::string& strName )
{
    if( m_mapNameExtractor.count( strName ) == 0 )
        return false;

    MapExtensionName_t::iterator p = m_mapExtensionName.find( strExtension );
    if( p != m_mapExtensionName.end() )
        return false;

    m_mapExtensionName[ strExtension ] = strName;
    return true;
}

const CTextExtractorFactory::MapExtensionName_t& CTextExtractorFactory::GetMapExtensionName()
{
    return m_mapExtensionName;
}

const CTextExtractorFactory::MapNameExtractor_t& CTextExtractorFactory::GetMapNameExtractor()
{
    return m_mapNameExtractor;
}

