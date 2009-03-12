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
    HANDLE handle;
#else
    size_t nCurrentIndex;
    glob_t gt;
#endif
public:
    GlobWrap( const std::string& strPath, const std::string& strMask );
    GlobWrap( const std::string& strPath );
    const char* NextFilename();
    ~GlobWrap();
};

#endif
