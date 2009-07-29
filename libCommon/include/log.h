#ifndef LOG_H
#define LOG_H

#include <boost/thread/recursive_mutex.hpp>
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

    static std::auto_ptr< std::ofstream > m_ptrLogFile;

    std::ofstream& GetFile();
    void TruncateFile();
    boost::recursive_mutex& GetLock();

    bool m_bMultiString;

public:

    CLog( LogLevelManip_t m, bool bMultiString = false );
    ~CLog();

    CLog& operator<<( const QString& str );
    CLog& operator<<( Manip_t m );
    
    template< class T > CLog& operator<<( const T& t )
    {
        GetFile() << t;
        return *this;
    }
};

char debug( CLog& );
char error( CLog& );

#endif // LOG_H
