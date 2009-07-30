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
          listSearchPaths( "searchgui/paths", QDir::currentPath() )
    {
    }

    Params& Conf()
    {
        static Params params;
        return params;
    }
}

