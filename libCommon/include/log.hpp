#ifndef LOG_H
#define LOG_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>

class CLog
{
public:

    CLog()
    {
        GetLock().lock();
    }

    ~CLog()
    {
        GetLock().unlock();
    }

private:

    CLog( const CLog& );
    const CLog& operator=( const CLog& );

    boost::mutex& GetLock()
    {
        static boost::mutex mtxLock;
        return mtxLock;
    }
};

template< class T >
        CLog& operator<<( CLog& log, const T& t )
{
    std::cout << t;
    return log;
}

#endif // LOG_H
