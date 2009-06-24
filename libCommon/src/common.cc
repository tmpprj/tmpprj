#include "common.h"

QString GetFileExtension( const QString& strFilename )
{
    int nPos = strFilename.lastIndexOf( '.' );
    if( nPos == -1 )
        return "";
    return strFilename.mid( nPos + 1 );
}
