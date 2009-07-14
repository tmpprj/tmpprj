#include "libsearch_common.h"
#include <log.hpp>

QByteArray StringToCommon( const QString& str, bool bCaseSensitive )
{
    if( bCaseSensitive )
        return str.toUtf8();
    else
        return str.toLower().toUtf8();
}

void ConvertListToPatterns( const QStringList& listPatterns, bool bCaseSensitive, PatternsContainer& patterns )
{
    for( int i = 0; i < listPatterns.size(); i++ )
    {
        QByteArray array = StringToCommon( listPatterns[ i ], bCaseSensitive );
        patterns.push_back( std::string( ( const char* )array.data(), array.size() ) );
    }
}

