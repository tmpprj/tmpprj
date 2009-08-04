#include "libsearch_common.h"
#include <log.h>

QByteArray StringToCommon( const QString& str, bool bCaseSensitive, bool bRaw )
{
    if( bCaseSensitive )
        return bRaw ? str.toAscii() : str.toUtf8();
    else
        return bRaw ? str.toLower().toAscii() : str.toLower().toUtf8();
}

void ConvertListToPatterns( const QStringList& listPatterns, bool bCaseSensitive, bool bRaw, PatternsContainer& patterns )
{
    for( int i = 0; i < listPatterns.size(); i++ )
    {
        QByteArray array = StringToCommon( listPatterns[ i ], bCaseSensitive, bRaw );
        patterns.push_back( std::string( ( const char* )array.data(), array.size() ) );
    }
}

