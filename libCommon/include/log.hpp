#ifndef LOG_H
#define LOG_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>
#include <fstream>

typedef std::ostream&( *Manip_t )( std::ostream& );

class CLog;
typedef char( *LogLevelManip_t )( CLog& );

class CLog
{
    CLog( const CLog& );
    const CLog& operator=( const CLog& );

    std::ofstream& GetFile()
    {
        static std::ofstream file( "system.log", std::ios_base::out | std::ios_base::app );
        return file;
    }
    
    boost::mutex m_mtxLock;

public:
    CLog()
    {
        m_mtxLock.lock();
        

    }

    virtual ~CLog()
    {
        m_mtxLock.unlock();
    }

    template< class T > CLog& operator<<( const T& t )
    {
        GetFile() << t;
        return *this;
    }


    CLog& operator<<( Manip_t m )
    {
        m( GetFile() );
        return *this;
    }
    
    CLog& operator<<( LogLevelManip_t m )
    {
        char chLogLevel = m( *this );
	   
        timeval tv;
        gettimeofday( &tv, NULL );
        tm* lpLocalTime = localtime( (time_t*)&tv.tv_sec );
    
        char buf[ 100 ];
    	sprintf( buf, "%02d.%02d.%d %02d:%02d:%02d.%03d %c: ",
                lpLocalTime->tm_mday, lpLocalTime->tm_mon + 1, lpLocalTime->tm_year + 1900,
                lpLocalTime->tm_hour, lpLocalTime->tm_min, lpLocalTime->tm_sec, (int)tv.tv_usec/1000,
                chLogLevel );

        GetFile() << buf;

        return *this;
    }
};

char debug( CLog& );
char error( CLog& );


class CUserLog
{
    std::ostringstream& GetStream()
    {
        static std::ostringstream stream;
        return stream;
    }

public:
    template< class T > CUserLog& operator<<( const T& t )
    {
        GetStream() << t;
        return *this;
    }

    CUserLog& operator<<( Manip_t m )
    {
        m( GetStream() );
        return *this;
    }

    std::string GetLogData()
    {
        return GetStream().str();
    }
};

#endif // LOG_H
