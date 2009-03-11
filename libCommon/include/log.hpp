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

    template< class T >
            CLog& operator<<( const T& t )
    {
        std::cout << t;
        return *this;
    }

    typedef std::ostream&(*Manip_t)( std::ostream& );

    CLog& operator<<( Manip_t m )
    {
        m( std::cout );
        return *this;
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


#endif // LOG_H
