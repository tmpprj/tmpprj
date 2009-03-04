#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

#include <string>
#include <mt_queue.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signal.hpp>

class CPlainTextExtractor: private boost::noncopyable
{
public:

    CPlainTextExtractor();

    ~CPlainTextExtractor()
    {
        OnStop();
    }

    boost::signal1< void, const std::string& >& SigDataObtained();

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

    boost::signal1< void, const std::string& > m_sigDataObtained;



    mt_queue<std::string> m_Queue;
};

#endif // CPLAINTEXTEXTRACTOR_H
