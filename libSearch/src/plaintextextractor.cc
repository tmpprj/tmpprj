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

boost::signals2::signal1< void, const QString& >& CPlainTextExtractor::SigFileProcessing()
{
    return m_sigFileProcessing;
}

void CPlainTextExtractor::WorkerFunc( const QString& strFileName )
{
    try
    {
        QTime timer;
        timer.start();
        
        //Process file
        QString strContent;
        m_sigFileProcessing( strFileName );

        ITextExtractor* pExtractor = TextExtractorFactory::Instance().GetExtractor( strFileName );
        
        CLog(debug) << "CPlainTextExtractor::WorkerFunc: processing " << qPrintable(strFileName) << " with " << pExtractor->GetName();
//        pExtractor->Extract( strFileName, strContent );
        
        structFileData Data = { strFileName, strContent };
        m_sigDataObtained( Data );
        
        CLog(debug) << "CPlainTextExtractor::WorkerFunc: (" << pExtractor->GetName() << "," << qPrintable(strFileName) << ") time elapsed: " << std::dec << timer.elapsed() << " ms";
    }
    catch( CUserLevelError& e )
    {
        SigError()( strFileName, e.whatQ() );
        CLog(error) << "CPlainTextExtractor::WorkerFunc: " << e.what();
    }
    catch( std::exception& e )
    {
        CLog(error) << "CPlainTextExtractor::WorkerFunc: (" << qPrintable(strFileName) << "): " << e.what();
    }
    catch( boost::thread_interrupted& )
    {
        throw;
    }
    catch( ... )
    {
        CLog(error) << "CPlainTextExtractor::WorkerFunc: (" << qPrintable(strFileName) << "): unknown error";
    }
}

CTextExtractorFactory::CTextExtractorFactory()
    : m_pDefaultExtractor( NULL )
{
    ITextExtractor* pExt = new CTxtTextExtractor;
    pExt = new CMsWordTextExtractor;
    RegisterName( pExt->GetName(), pExt );
    pExt = new CXlsTextExtractor;
    RegisterName( pExt->GetName(), pExt );
    pExt = new CPptTextExtractor;
    RegisterName( pExt->GetName(), pExt );
    pExt = new CPdfTextExtractor;
    RegisterName( pExt->GetName(), pExt );


    pExt = new CTxtTextExtractor;
    RegisterName( pExt->GetName(), pExt );
    m_pDefaultExtractor = pExt;
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
    CLog(debug) << "CTextExtractorFactory::RegisterName: " << strName << " registred";
    MapNameExtractor_t::iterator p = m_mapNameExtractor.find( strName );

    if( p != m_mapNameExtractor.end() )
        return false;
    
    m_mapNameExtractor[ strName ] = pTextExtractor;
    return true;
}

bool CTextExtractorFactory::RegisterExtension( const QString& strExtension, const QString& strName )
{
    CLog(debug) << "CTextExtractorFactory::RegisterExtension: " << strExtension << ":" << strName << " registred";
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

