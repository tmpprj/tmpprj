#include "search_conf.h"
#include "settings.h"

SearchParams::SearchParams()
    : stCharDetBlockSize( "search/charset-detect-block-size", "1024" )
{
}

SearchParams& SearchConf()
{
    static SearchParams params;
    return params;
}
