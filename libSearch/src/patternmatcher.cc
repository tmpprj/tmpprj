#include "patternmatcher.h"
#include "log.hpp"

CPatternMatcher::CPatternMatcher()
{
}

void CPatternMatcher::ThreadFunc( boost::barrier* pvarBarrier )
{
    pvarBarrier->wait();
    
    m_searcher.LoadPatterns( m_patterns );

    for(;;)
    {
        FileInfo info = m_Queue.pop();

        boost::this_thread::interruption_point();

        int nFoundPatterns = m_searcher.FindPatterns( std::string( ( const char* )info.strFiledata.utf16(), 
                    info.strFiledata.size() * 2 ) );
        bool bFileGood = ( ( size_t )nFoundPatterns == m_searcher.GetPatternCount() );
        m_sigFileProcessed( info.strFilename, bFileGood );
    }
}

void CPatternMatcher::SetPatterns( const PatternsContainer& patterns )
{
    m_patterns = patterns;
}

void CPatternMatcher::OnNewFile( const std::string& strFilename, const QString& strFiledata )
{
    FileInfo info = { strFilename, strFiledata };
    m_Queue.push( info );
    
    boost::unique_lock<boost::mutex> lock( m_mutAccess );
    if( !m_ptrThread.get() )
    {
        boost::barrier varBarrier( 2 );
        
        boost::function0< void > threadFunc = boost::bind( &CPatternMatcher::ThreadFunc, this, &varBarrier );
        m_ptrThread = ThreadPtr_t( new boost::thread( threadFunc ) );
        varBarrier.wait();
    }
}

void CPatternMatcher::OnStop()
{
    boost::unique_lock<boost::mutex> lock( m_mutAccess );

    if( m_ptrThread.get() )
    {
        m_ptrThread->interrupt();
        m_Queue.push( FileInfo() );
        m_ptrThread->join();
        m_ptrThread.reset();
    }
}

boost::signal2< void, const std::string&, bool >& CPatternMatcher::SigFileProcessed()
{
    return m_sigFileProcessed;
}

CPatternMatcher::~CPatternMatcher()
{
    OnStop();
}
