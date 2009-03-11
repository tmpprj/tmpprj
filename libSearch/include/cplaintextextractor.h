#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

#include <string>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <boost/filesystem.hpp>
#include <QString>
#include <singleton.hpp>
#include <mt_queue.hpp>

class CPlainTextExtractor: private boost::noncopyable
{
public:

    CPlainTextExtractor();

    ~CPlainTextExtractor()
    {
        OnStop();
    }

    boost::signal1< void, const QString& >& SigDataObtained();

    void OnNewFile( const std::string& strFileName )
    {
        if( !strFileName.empty() )
            m_Queue.push( strFileName );

        if( NULL == m_pThread.get() )
        {
            boost::lock_guard<boost::mutex> lock( m_mtxStopSync );
            boost::mutex mtxThreadStarted;
            mtxThreadStarted.lock();

            m_pThread = boost::shared_ptr<boost::thread>( new boost::thread( boost::bind( &CPlainTextExtractor::ThreadFunc, this, &mtxThreadStarted ) ) );

            mtxThreadStarted.lock();
        }
    }

    void OnStop()
    {
        boost::lock_guard<boost::mutex> lock( m_mtxStopSync );
        if( NULL != m_pThread.get() )
        {
            m_pThread->interrupt();
            m_Queue.push( "" );
            m_pThread->join();
            m_pThread.reset();
            //TODO: clear queue
        }
    }

private:

    boost::mutex m_mtxStopSync;

    boost::shared_ptr< boost::thread > m_pThread;

    void ThreadFunc( boost::mutex* pmtxThreadStarted )
    {
        pmtxThreadStarted->unlock();
        std::string strFileName = m_Queue.pop();

        boost::this_thread::interruption_point();

        //Process file

    }

    boost::signal1< void, const QString& > m_sigDataObtained;

    mt_queue<std::string> m_Queue;
};

class ITextExtractor
{
public:

    virtual ~ITextExtractor(){}

    virtual void Extract( const std::string strFileName, QString& strText ) = 0;
};

class CTextExtractorFactory
{
public:

    ITextExtractor* GetExtractor( const std::string& strFileName )
    {
        boost::filesystem::path file( strFileName );
        if( mapExtractors.end() == mapExtractors.find( file.extension() ) )
            return mapExtractors[ ".txt" ];
        else
            return mapExtractors[ file.extension() ];
    }

    bool RegisterExtractor( const std::string& strFormat, ITextExtractor* pTextExtractor )
    {
        mapExtractors[ strFormat ] = pTextExtractor;
        return true;
    }

private:

    std::map< std::string, ITextExtractor* > mapExtractors;

};

typedef Singleton<CTextExtractorFactory> TextExtractorFactory;

#endif // CPLAINTEXTEXTRACTOR_H
