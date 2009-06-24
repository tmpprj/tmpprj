#include "searchgui_conf.h"
#include "settings.h"

namespace SearchGUI
{
    Params::Params()
        : mapExtensions( "searchgui/extensions" ),
          bCaseSensitive( "searchgui/case-sensitive" ),
          listMasks( "searchgui/masks" ),
          listSearches( "searchgui/searches" ),
          listSearchPaths( "searchgui/paths" )
    {
    }

    Params& Conf()
    {
        static Params params;
        return params;
    }
}

