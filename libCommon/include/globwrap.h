#ifndef _GLOBWRAP_H_
#define _GLOBWRAP_H_

#include <string>

#ifdef WIN32
#include <windows.h>
#else
#include <glob.h>
#endif


class GlobWrap
{
#ifdef WIN32
    WIN32_FIND_DATAA m_Data;
    HANDLE m_Handle;
    std::string m_strBuf;
    std::string m_strPath;
    bool m_bOnlyDir;
#else
    size_t nCurrentIndex;
    glob_t gt;
#endif
public:
    GlobWrap( const std::string& strPath, const std::string& strMask );
    GlobWrap( const std::string& strPath );
    std::string NextFilename();
    ~GlobWrap();
};

#endif
