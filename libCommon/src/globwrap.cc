#include "globwrap.h"

#ifdef WIN32

    GlobWrap::GlobWrap( const std::string& strPath, const std::string& strMask )
    {
    
    }

    GlobWrap::GlobWrap( const std::string& strPath )
    {
    }

    const char* GlobWrap::NextFilename()
    {

    }

    GlobWrap::~GlobWrap()
    {
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

    const char* GlobWrap::NextFilename()
    {
        if( nCurrentIndex < gt.gl_pathc )
            return gt.gl_pathv[ nCurrentIndex++ ];

        return NULL;
    }

    GlobWrap::~GlobWrap()
    {
        globfree( &gt );
    }

#endif
