#ifndef LOG_H
#define LOG_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>
#include <fstream>
#include <QTime>

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
    
    boost::mutex& GetLock()
    {
        static boost::mutex mtxLock;
        return mtxLock;
    }

public:

    CLog( LogLevelManip_t m )
    {
        GetLock().lock();

        GetFile() << QTime::currentTime().toString( "HH:mm:ss:zzz" ).toStdString() << " ["<< m( *this ) << "]: ";
    }

    virtual ~CLog()
    {
        GetLock().unlock();

        GetFile() << std::endl;
    }

    template< class T > CLog& operator<<( const T& t )
    {
        GetFile() << t;
        return *this;
    }

    CLog& operator<<( const QString& str )
    {
        GetFile() << str.toStdString();
        return *this;
    }

    CLog& operator<<( Manip_t m )
    {
        m( GetFile() );
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
