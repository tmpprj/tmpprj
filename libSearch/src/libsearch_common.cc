#include "libsearch_common.h"

void ConvertListToPatterns( const QStringList& listPatterns, bool bCaseSensitive, PatternsContainer& patterns )
{
    for( int i = 0; i < listPatterns.size(); i++ )
    {
        QString strData;
        if( bCaseSensitive )
            strData = listPatterns[ i ];
        else
            strData = listPatterns[ i ].toLower();

        patterns.push_back( std::string( ( const char* )strData.utf16(), strData.size() * 2 ) );
    }
}

