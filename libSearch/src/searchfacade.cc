#include "searchfacade.h"
#include "filesearcher.h"

void SearchFacade::StartSearch( const std::string& strPath, const Masks_t& vMasks )
{
    m_searcher.StartSearch( strPath, vMasks );
}

void SearchFacade::Stop()
{
    m_sigStop();
}

boost::signal0< void >& SearchFacade::SigStop()
{
    return m_sigStop;
}

boost::signal1< void, const std::string& >& SearchFacade::SigFileProcessed()
{
    return m_searcher.SigFileProcessed();
}

