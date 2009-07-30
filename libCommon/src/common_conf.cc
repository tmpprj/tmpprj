#include "common_conf.h"
#include "settings.h"

CommonParams::CommonParams()
    : nMaxLogSize( "common/max-log-size", 1048576 )
{
}

CommonParams& CommonConf()
{
    static CommonParams params;
    return params;
}
