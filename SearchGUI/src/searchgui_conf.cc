#include "searchgui_conf.h"
#include "settings.h"

namespace SearchGUI
{
    Params::Params()
        : mapExtensions( "searchgui/extensions" ),
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

