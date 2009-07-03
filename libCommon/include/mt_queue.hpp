#ifndef _MTQUEUE_H_
#define _MTQUEUE_H_

#include <queue>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

template < class T >
class mt_queue
{
    std::queue< T > m_queue;
    boost::shared_mutex m_mtxAccess;
    boost::interprocess::interprocess_semaphore m_smpQueueEmpty;
    boost::interprocess::interprocess_semaphore m_smpQueueFull;

public:
    mt_queue( int nMaxSize )
        : m_smpQueueEmpty( 0 ),
          m_smpQueueFull( nMaxSize )
    {
    }

    bool empty()
    {
        boost::shared_lock< boost::shared_mutex > lock( m_mtxAccess );
        return m_queue.empty();
    }

    size_t size()
    {
        boost::shared_lock< boost::shared_mutex > lock( m_mtxAccess );
        return m_queue.size();
    }

    void clear()
    {
        while( !pop() );
    }

    void push( const T& elem )
    {
        m_smpQueueFull.wait();
        boost::unique_lock< boost::shared_mutex > lock( m_mtxAccess );
        
        m_queue.push( elem );
        m_smpQueueEmpty.post();
    }

    bool pop()
    {
        m_smpQueueEmpty.wait();
        boost::unique_lock< boost::shared_mutex > lock( m_mtxAccess );

        m_queue.pop();
        m_smpQueueFull.post();
        return m_queue.empty();
    }

    const T front()
    {
        m_smpQueueEmpty.wait();
        boost::unique_lock< boost::shared_mutex > lock( m_mtxAccess );

        const T elem = m_queue.front();
        m_smpQueueEmpty.post();
        return elem;
    }
};

#endif

