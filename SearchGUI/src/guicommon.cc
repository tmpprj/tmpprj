#include "guicommon.h"

#include <macro.h>
#include <boost/foreach.hpp>
#include <log.hpp>

QString FormatExtension( const QString& strExt )
{
    QString strRet;

    for( int i = 0; i < strExt.size(); i++ )
        if( strExt[ i ].isLetterOrNumber() )
            strRet += strExt[ i ];

    return "." + strRet;
}

void ParsePatterns( const QString& strText, QStringList& listPatterns )
{
    int nStart = 0;
    bool bCommaBlock = false;

    for( int i = 0; i <= strText.size(); i++ )
        if( i == strText.size() )
        {
            if( !bCommaBlock )
                listPatterns.push_back( strText.mid( nStart, i - nStart ).trimmed() );
        }
        else if( strText[ i ] == '"' )
        {
            if( bCommaBlock )
                listPatterns.push_back( strText.mid( nStart, i - nStart ).trimmed() );

            bCommaBlock = !bCommaBlock;
            nStart = i + 1;
        }
        else if( strText[ i ] == ' ' )
        {
            if( !bCommaBlock )
            {
                listPatterns.push_back( strText.mid( nStart, i - nStart ).trimmed() );
                nStart = i + 1;
            }
        }
}

void ParseMasks( const QString& strMasks, QStringList& listMasks )
{
    listMasks = strMasks.split( ";", QString::SkipEmptyParts );
    for( int i = 0; i < listMasks.size(); i++ )
        listMasks[ i ] = listMasks[ i ].trimmed();
}

