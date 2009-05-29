#include "globwrap.h"

#ifdef WIN32

#include "windows.h"

    GlobWrap::GlobWrap( const std::string& strPath, const std::string& strMask )
            :m_strPath( strPath )
    {
        m_Handle = ::FindFirstFileA( ( strPath + "/" + strMask ).c_str(), &m_Data );
        if( INVALID_HANDLE_VALUE != m_Handle )
            m_strBuf = m_Data.cFileName;
    }

    GlobWrap::GlobWrap( const std::string& strPath )
            :m_strPath( strPath )
    {
        m_Handle = ::FindFirstFileA( strPath.c_str(), &m_Data );
        if( INVALID_HANDLE_VALUE != m_Handle )
            m_strBuf = m_Data.cFileName;
    }

    std::string GlobWrap::NextFilename()
    {
        if( !m_strBuf.empty() )
        {
            std::string strTmp = m_strBuf;

            if( ::FindNextFileA( m_Handle, &m_Data ) )
                m_strBuf = m_Data.cFileName;
            else
                m_strBuf.clear();

            return m_strPath + "/" + strTmp;
        }

        return std::string();
    }

    GlobWrap::~GlobWrap()
    {
        if( INVALID_HANDLE_VALUE )
            ::FindClose( m_Handle );
    }


#else

    #include <glob.h>

    GlobWrap::GlobWrap( const std::string& strPath, const std::string& strMask )
    : nCurrentIndex( 0 )
    {
        glob( ( strPath + "/" + strMask ).c_str(), GLOB_NOSORT, NULL, &gt );
    }

    GlobWrap::GlobWrap( const std::string& strPath )
    : nCurrentIndex( 0 )
    {
        glob( ( strPath + "/*" ).c_str(), GLOB_ONLYDIR | GLOB_NOSORT, NULL, &gt );
    }

    std::string GlobWrap::NextFilename()
    {
        if( nCurrentIndex < gt.gl_pathc )
            return std::string( gt.gl_pathv[ nCurrentIndex++ ] );

        return std::string();
    }

    GlobWrap::~GlobWrap()
    {
        globfree( &gt );
    }

#endif
