#include "searchfacade.h"
#include "filesearcher.h"

CSearchFacade::CSearchFacade()
{
    m_sigStop.connect( boost::bind( &CFileSearcher::OnStop, &m_searcher ) );
    m_sigStop.connect( boost::bind( &CPlainTextExtractor::OnStop, &m_extractor ) );

    m_searcher.SigFileProcessed().connect( boost::bind( &CPlainTextExtractor::OnNewFile, &m_extractor, _1 ) );
}

void CSearchFacade::Start( const std::string& strPath, const Masks_t& vMasks )
{
    m_searcher.StartSearch( strPath, vMasks );
}

void CSearchFacade::Stop()
{
    m_sigStop();
}

boost::signal1< void, const std::string& >& CSearchFacade::SigFileFound()
{
    return m_searcher.SigFileProcessed();
}

boost::signal2< void, const std::string&, const QString& >& CSearchFacade::SigFileProcessed()
{
    return m_extractor.SigDataObtained();
}
