#include "log.h"
#include "common_conf.h"

std::auto_ptr< std::ofstream > CLog::m_ptrLogFile;


CLog::CLog( LogLevelManip_t m, bool bMultiString )
: m_bMultiString( bMultiString )
{
    GetLock().lock();

    if( GetFile().tellp() > CommonConf().nMaxLogSize.Value() )
        TruncateFile();

    GetFile() << QTime::currentTime().toString( "HH:mm:ss:zzz" ).toStdString() << " ["<< m( *this ) << "]: ";
}

CLog::~CLog()
{
    if( !m_bMultiString )
        GetFile() << std::endl;
    
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


char debug( CLog& )
{
    return 'D';
}

char error( CLog& )
{
    return 'E';
}

