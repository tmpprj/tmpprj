#ifndef __DATAHANDLER__HPP
#define __DATAHANDLER__HPP

#include <boost/signals2.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <mt_queue.hpp>
#include <log.h>

template< typename DataType >
class CDataHandler: private boost::noncopyable
{
public:
    CDataHandler( int nMaxQueueSize )
        : m_Queue( nMaxQueueSize )
    {
    }

    virtual ~CDataHandler()
    {
        OnStop();
    }

    void OnData( const DataType& Data )
    {
        m_Queue.push( Data );

        boost::lock_guard<boost::mutex> lock( m_mtxStopSync );
        if( NULL == m_pThread.get() )
        {
            boost::mutex mtxThreadStarted;
            mtxThreadStarted.lock();

            m_pThread = boost::shared_ptr<boost::thread>( new boost::thread( boost::bind( &CDataHandler<DataType>::ThreadFunc, this, &mtxThreadStarted ) ) );

            mtxThreadStarted.lock();
            mtxThreadStarted.unlock();
        }
        
    }

    void OnStop()
    {
        boost::lock_guard<boost::mutex> lock( m_mtxStopSync );
        if( NULL != m_pThread.get() )
        {
            m_pThread->interrupt();
            m_pThread->join();
            m_pThread.reset();
            m_Queue.clear();
            m_sigQueueEmpty();
        }
    }

    boost::signals2::signal0< void >& SigQueueEmpty()
    {
        return m_sigQueueEmpty;
    }

    boost::signals2::signal2< void, const QString&, const QString& >& SigError()
    {
        return m_sigError;
    }

    bool IsQueueEmpty()
    {
        return m_Queue.empty();
    }

private:

    boost::mutex m_mtxStopSync;

    boost::shared_ptr< boost::thread > m_pThread;

    boost::signals2::signal0< void > m_sigQueueEmpty;

    boost::signals2::signal2< void, const QString&, const QString& > m_sigError;

    void ThreadFunc( boost::mutex* pmtxThreadStarted )
    {
        try
        {
            pmtxThreadStarted->unlock();

            for(;;)
            {
                DataType Data = m_Queue.front();
                boost::this_thread::interruption_point();
                WorkerFunc( Data );
                bool bEmpty = m_Queue.pop();
                if( bEmpty )
                    m_sigQueueEmpty();
            }
        }
        catch( boost::thread_interrupted& )
        {
            CLog(Debug) << "DataHandler::ThreadFunc: thread closed";
        }
        catch( std::exception& e )
        {
            CLog(Error) << "DataHandler::ThreadFunc error: " << e.what();
        }
        catch( ... )
        {
            CLog(Error) << "DataHandler::ThreadFunc: unknown error";
        }
    }

    virtual void WorkerFunc( const DataType& Data ) = 0;

    mt_queue<DataType> m_Queue;

};

#endif
