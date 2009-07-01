#include "txttextextractor.h"
#include "plaintextextractor.h"
#include "mswordtextextractor.h"
#include "pdftextextractor.h"

#include <log.hpp>
#include <common.h>
#include <boost/foreach.hpp>
#include <exceptions.h>

#include <QThread>

boost::signals2::signal1< void, const CPlainTextExtractor::structFileData& >& CPlainTextExtractor::SigDataObtained()
{
    return m_sigDataObtained;
}

void CPlainTextExtractor::WorkerFunc( const QString& strFileName )
{
    CLog( debug ) << "EXTRACTOR THREAD: " << QThread::currentThreadId() << std::endl;
    try
    {
        //Process file
        QString strContent;
        TextExtractorFactory::Instance().GetExtractor( strFileName )->Extract( strFileName, strContent );
        structFileData Data = { strFileName, strContent };
        m_sigDataObtained( Data );
    }
    catch( CUserLevelError& e )
    {
        SigError()( strFileName, e.whatQ() );
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

ITextExtractor* CTextExtractorFactory::GetExtractor( const QString& strFileName )
{
    QString strExt = GetFileExtension( strFileName );

    MapExtensionName_t::iterator pExtName = m_mapExtensionName.find( strExt );
    if( pExtName == m_mapExtensionName.end() )
        return m_pDefaultExtractor;

    MapNameExtractor_t::iterator pNameExtractor = m_mapNameExtractor.find( pExtName->second );
    if( pNameExtractor == m_mapNameExtractor.end() )
        return m_pDefaultExtractor;
    
    return pNameExtractor->second;
}


bool CTextExtractorFactory::RegisterName( const QString& strName, ITextExtractor* pTextExtractor )
{
    MapNameExtractor_t::iterator p = m_mapNameExtractor.find( strName );

    if( p != m_mapNameExtractor.end() )
        return false;
    
    m_mapNameExtractor[ strName ] = pTextExtractor;
    return true;
}

bool CTextExtractorFactory::RegisterExtension( const QString& strExtension, const QString& strName )
{
    if( m_mapNameExtractor.count( strName ) == 0 )
        return false;

    QString strExtensionLower = strExtension.toLower();
    MapExtensionName_t::iterator p = m_mapExtensionName.find( strExtensionLower );
    if( p != m_mapExtensionName.end() )
        return false;

    m_mapExtensionName[ strExtensionLower ] = strName;
    return true;
}

void CTextExtractorFactory::ClearExtensions()
{
    m_mapExtensionName.clear();
}

const CTextExtractorFactory::MapExtensionName_t& CTextExtractorFactory::GetMapExtensionName()
{
    return m_mapExtensionName;
}

const CTextExtractorFactory::MapNameExtractor_t& CTextExtractorFactory::GetMapNameExtractor()
{
    return m_mapNameExtractor;
}

