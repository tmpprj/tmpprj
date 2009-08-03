#include "documentchecker.h"
#include "libsearch_common.h"
#include "patterncounter.h"
#include "txttextextractor.h"
#include "search_conf.h"

#include <log.h>
#include <exceptions.h>
#include <boost/concept_check.hpp>

CDocumentChecker::CDocumentChecker()
    : CDataHandler< QString >( SearchConf().nCheckerQueueSize.Value() )
{
}

void CDocumentChecker::SetSearchParameters( const QStringList& listPatterns, bool bCaseSensitive )
{
    m_ptrCounter = std::auto_ptr< CPatternCounter >( 
            new CPatternCounter( listPatterns, bCaseSensitive, SearchConf().nChunkOverlap.Value() ) );
}

boost::signals2::signal1< void, const QString& >& CDocumentChecker::SigFileProcessing()
{
    return m_sigFileProcessing;
}

boost::signals2::signal1< void, const QString& >& CDocumentChecker::SigFileMatched()
{
    return m_sigFileMatched;
}

void CDocumentChecker::WorkerFunc( const QString& strFileName )
{
    try
    {
        m_sigFileProcessing( strFileName );
        
        QTime timer;
        timer.start();

        m_ptrCounter->ClearResult();
        if( m_ptrCounter->SomePatterns() )
        {
            ITextExtractor* pExtractor = TextExtractorFactory::Instance().GetExtractor( strFileName );
            CLog( Debug ) << "Processing file " << qPrintable( strFileName ) <<
                    " with parser " << pExtractor->GetName();

            boost::signals2::scoped_connection scoped_conn1, scoped_conn2;
            scoped_conn1 = pExtractor->SigChunk().connect(
                    boost::bind( &CPatternCounter::OnChunk, m_ptrCounter.get(), _1 ) );
            scoped_conn2 = pExtractor->SigChunkIsRaw().connect(
                    boost::bind( &CPatternCounter::OnChunkIsRaw, m_ptrCounter.get(), _1 ) );

            pExtractor->Extract( strFileName, SearchConf().nFileChunkSize.Value() );
        }
        else
            CLog( Debug ) << "Processing file " << qPrintable( strFileName ) << " - empty patterns";

        CLog( Debug ) << "Matched ok: " << m_ptrCounter->MatchedOk() << 
            dec << " time elapsed: " << timer.elapsed() << " ms" << std::endl;

        if( m_ptrCounter->MatchedOk() )
            m_sigFileMatched( strFileName );
    }
    catch( CUserLevelError& e )
    {
        SigError()( strFileName, e.whatQ() );
        CLog( Error ) << "CDocumentChecker::WorkerFunc: " << e.what();
    }
    catch( std::exception& e )
    {
        CLog( Error ) << "CDocumentChecker::WorkerFunc: (" << qPrintable(strFileName) << "): " << e.what();
    }
    catch( boost::thread_interrupted& )
    {
        CLog( Error ) << "CDocumentChecker::WorkerFunc: interrupted";
        throw;
    }
    catch( ... )
    {
        CLog( Error ) << "CDocumentChecker::WorkerFunc: (" << qPrintable(strFileName) << "): unknown error";
    }
}
