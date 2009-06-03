#include "searchgui_conf.h"
#include "settings.h"

namespace SearchGUI
{
    Params::Params()
    {
        extensions = Settings().value( "searchgui/settings" ).toMap();
        searchPaths = Settings().value( "searchgui/paths" ).toStringList();
        searches = Settings().value( "searchgui/searches" ).toStringList();
    }

    Params::~Params()
    {
        Settings().setValue( "searchgui/settings", extensions );
        Settings().setValue( "searchgui/paths", searchPaths );
        Settings().setValue( "searchgui/searches", searches );
    }

    Params& Conf()
    {
        static Params params;
        return params;
    }
}

