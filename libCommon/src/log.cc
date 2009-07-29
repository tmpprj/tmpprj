#include "log.h"
#include "common_conf.h"

std::auto_ptr< std::ofstream > CLog::m_ptrLogFile;

char GetLevelChar( LogLevel level )
{
    switch( level )
    {
        case Debug:
            return 'D';
        case Error:
            return 'E';
    }
    return ' ';
}


CLog::CLog( LogLevel level, bool bMultiString )
: m_level( level ),
  m_bMultiString( bMultiString )
{
    GetLock().lock();

    if( GetFile().tellp() > CommonConf().nMaxLogSize.Value() )
        TruncateFile();

    GetFile() << QTime::currentTime().toString( "HH:mm:ss:zzz" ).toStdString() << " ["<< GetLevelChar( level ) << "]: ";
}

CLog::~CLog()
{
    if( !m_bMultiString )
        AddNewLine();
    
    GetLock().unlock();
}

std::ofstream& CLog::GetFile()
{
    if( !m_ptrLogFile.get() )
        m_ptrLogFile = std::auto_ptr< std::ofstream >( 
                new std::ofstream( "system.log", std::ios_base::out | std::ios_base::app ) );
    return *m_ptrLogFile.get();
}

void CLog::TruncateFile()
{
    m_ptrLogFile = std::auto_ptr< std::ofstream >( 
            new std::ofstream( "system.log", std::ios_base::out ) );
}

void CLog::AddNewLine()
{
#ifdef BUILD_RELEASE
    if( m_level == Debug )
        return;
#endif
    GetFile() << std::endl;
}

boost::recursive_mutex& CLog::GetLock()
{
    static boost::recursive_mutex mtxLock;
    return mtxLock;
}

CLog& CLog::operator<<( const QString& str )
{
    GetFile() << str.toStdString();
    return *this;
}

CLog& CLog::operator<<( Manip_t m )
{
    m( GetFile() );
    return *this;
}
