#ifndef __DATAHANDLER__HPP
#define __DATAHANDLER__HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <mt_queue.hpp>

template< typename DataType >
class CDataHandler: private boost::noncopyable
{
public:

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
            m_Queue.push( DataType() );
            m_pThread->join();
            m_pThread.reset();
            m_Queue.clear();
        }
    }

private:

    boost::mutex m_mtxStopSync;

    boost::shared_ptr< boost::thread > m_pThread;

    void ThreadFunc( boost::mutex* pmtxThreadStarted )
        {
            pmtxThreadStarted->unlock();

            for(;;)
            {
                DataType Data = m_Queue.pop();
                boost::this_thread::interruption_point();
                WorkerFunc( Data );
            }
        }

    virtual void WorkerFunc( const DataType& Data ) = 0;

    mt_queue<DataType> m_Queue;

};

#endif
