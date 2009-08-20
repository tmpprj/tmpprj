#include "searchgui_conf.h"
#include "settings.h"
#include "macro.h"
#include "plaintextextractor.h"

namespace SearchGUI
{
    bool ExtensionsValidator( QMap< QString, QVariant >& Ext )
    {
        std::vector< QString > vecRemove;

        const std::map< QString, ITextExtractor* >& mapExtractors = TextExtractorFactory::Instance().GetMapNameExtractor();
        FOREACH( e, Ext )
        {
            if( mapExtractors.end() == mapExtractors.find( e.value().value<QString>() ) )
                vecRemove.push_back( e.key() );
        }

        FOREACH( key, vecRemove )
            Ext.remove( *key );

        return true;
    }

    Params::Params()
        : mapExtensions( "searchgui/extensions", QVariant(), ExtensionsValidator ),
          bCaseSensitive( "searchgui/case-sensitive", false ),
          bRecursive( "searchgui/recursive", true ),
          listMasks( "searchgui/masks", "*" ),
          listSearches( "searchgui/searches" ),
          listSearchPaths( "searchgui/paths", QDir::currentPath() ),
          bFileSizeLimits( "searchgui/filesizelimits", false ),
          ullMinFileSize( "searchgui/minfilesize", 0, BoundsValidator<unsigned long long>( 0, 10240000 ) ),
          ullMaxFileSize( "searchgui/maxfilesize", 102400, BoundsValidator<unsigned long long>( 0, 10240000 ) ),
          bCharsetDetect( "searchgui/charsetdetect", true ),
          nMaxFiles( "searchgui/maxfilesnumber", 10000 )
    {
    }

    Params& Conf()
    {
        static Params params;
        return params;
    }
}

