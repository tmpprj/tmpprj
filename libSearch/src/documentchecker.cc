#include "documentchecker.h"
#include "libsearch_common.h"
#include "patterncounter.h"
#include "txttextextractor.h"
#include "search_conf.h"

#include <log.hpp>
#include <exceptions.h>
#include <boost/concept_check.hpp>

CDocumentChecker::CDocumentChecker()
    : CDataHandler< QString >( SearchConf().nCheckerQueueSize.Value() )
{
}

void CDocumentChecker::SetSearchParameters( const QStringList& listPatterns, bool bCaseSensitive )
{
    m_bCaseSensitive = bCaseSensitive;

    PatternsContainer patterns;
    ConvertListToPatterns( listPatterns, m_bCaseSensitive, patterns );

    m_searcher.LoadPatterns( patterns );
}

boost::signals2::signal1< void, const QString& >& CDocumentChecker::SigFileProcessing()
{
    return m_sigFileProcessing;
}

boost::signals2::signal1< void, const QString& >& CDocumentChecker::SigFileMatched()
{
    return m_sigFileMatched;
}

int Func( const QString& str )
{
    boost::ignore_unused_variable_warning( str );
    return 123;
}

void CDocumentChecker::WorkerFunc( const QString& strFileName )
{
    try
    {
        m_sigFileProcessing( strFileName );

        CPatternCounter counter( m_searcher );
        ITextExtractor* pExtractor = TextExtractorFactory::Instance().GetExtractor( strFileName );
        CLog( debug ) << "Processing file " << qPrintable( strFileName ) <<
                " with parser " << pExtractor->GetName();

        boost::signals2::scoped_connection scoped_conn;
        scoped_conn = pExtractor->SigChunk().connect(
                boost::bind( &CPatternCounter::OnChunk, &counter, _1 ) );

        pExtractor->Extract( strFileName, SearchConf().nFileChunkSize.Value() );

        CLog( debug ) << "Matched ok: " << counter.MatchedOk() << std::endl;
        if( counter.MatchedOk() )
            m_sigFileMatched( strFileName );
    }
    catch( CUserLevelError& e )
    {
        SigError()( strFileName, e.whatQ() );
        CLog( error ) << "CDocumentChecker::WorkerFunc: " << e.what();
    }
    catch( std::exception& e )
    {
        CLog( error ) << "CDocumentChecker::WorkerFunc: (" << qPrintable(strFileName) << "): " << e.what();
    }
    catch( boost::thread_interrupted& )
    {
        CLog( error ) << "CDocumentChecker::WorkerFunc: interrupted";
        throw;
    }
    catch( ... )
    {
        CLog( error ) << "CDocumentChecker::WorkerFunc: (" << qPrintable(strFileName) << "): unknown error";
    }
}
