#ifndef _MTQUEUE_H_
#define _MTQUEUE_H_

#include <queue>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

template < class T >
class mt_queue
{
    std::queue< T > m_queue;
    int m_nMaxSize;
    boost::recursive_mutex m_mtxAccess;

    void waitWhileQueueEmpty()
    {
        while( true )
        {
            boost::this_thread::interruption_point();
            m_mtxAccess.lock();
            if( m_queue.size() > 0 )
                return;                 // Return while access mutex locked - save current transaction
            m_mtxAccess.unlock();

            boost::this_thread::sleep( boost::posix_time::milliseconds( 20 ) );
        }
    }

    void waitWhileQueueFull()
    {
        while( true )
        {
            boost::this_thread::interruption_point();
            m_mtxAccess.lock();
            if( ( int )m_queue.size() < m_nMaxSize || m_nMaxSize == -1 )
                return;                 // Return while access mutex locked - save current transaction
            m_mtxAccess.unlock();

            boost::this_thread::sleep( boost::posix_time::milliseconds( 20 ) );
        }
    }

public:
    mt_queue( int nMaxSize )
        : m_nMaxSize( nMaxSize )
    {
    }

    bool empty()
    {
        boost::unique_lock< boost::recursive_mutex > lock( m_mtxAccess );
        return m_queue.empty();
    }

    size_t size()
    {
        boost::unique_lock< boost::recursive_mutex > lock( m_mtxAccess );
        return m_queue.size();
    }

    void clear()
    {
        boost::unique_lock< boost::recursive_mutex > lock( m_mtxAccess );

        while( m_queue.size() > 0 )
            m_queue.pop();
    }

    void push( const T& elem )
    {
        waitWhileQueueFull();
        m_queue.push( elem );
        m_mtxAccess.unlock();
    }

    bool pop()
    {
        waitWhileQueueEmpty();
        m_queue.pop();
        bool ret = m_queue.empty();
        m_mtxAccess.unlock();

        return ret;
    }

    const T front( bool bErase = false )
    {
        waitWhileQueueEmpty();
        const T elem = m_queue.front();
        if( bErase )
            m_queue.pop();
        m_mtxAccess.unlock();
        
        return elem;
    }
};

#endif

