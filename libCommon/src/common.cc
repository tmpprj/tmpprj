#include "common.h"

QString GetFileExtension( const QString& strFileName )
{
    int nPos = strFileName.lastIndexOf( '.' );
    if( nPos == -1 )
        return "";

    return strFileName.mid( nPos ).toLower();
}
