#ifndef LOG_H
#define LOG_H

#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>
#include <fstream>
#include <QTime>

typedef std::ostream&( *Manip_t )( std::ostream& );

enum LogLevel { Debug, Error };

class CLog
{
    CLog( const CLog& );
    const CLog& operator=( const CLog& );

    static std::auto_ptr< std::ofstream > m_ptrLogFile;

    std::ofstream& GetFile();
    void TruncateFile();
    void AddNewLine();
    boost::recursive_mutex& GetLock();

    LogLevel m_level;
    bool m_bMultiString;

public:

    CLog( LogLevel level, bool bMultiString = false );
    ~CLog();

    CLog& operator<<( const QString& str );
    CLog& operator<<( Manip_t m );
    
    template< class T > CLog& operator<<( const T& t )
    {
#ifdef BUILD_RELEASE
        if( m_level == Debug )
            return *this;
#endif
        GetFile() << t;
        return *this;
    }
};

#endif // LOG_H
