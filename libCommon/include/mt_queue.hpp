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
    boost::interprocess::interprocess_semaphore m_smpQueue;

public:
    mt_queue()
        : m_smpQueue( 0 )
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

    void push( const T& elem )
    {
        boost::unique_lock< boost::shared_mutex > lock( m_mtxAccess );
        m_queue.push( elem );
        m_smpQueue.post();
    }

    const T pop()
    {
        m_smpQueue.wait();
        boost::unique_lock< boost::shared_mutex > lock( m_mtxAccess );

        const T elem = m_queue.front();
        m_queue.pop();
        return elem;
    }
};


#endif

