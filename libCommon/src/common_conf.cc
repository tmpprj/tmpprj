#include "common_conf.h"
#include "settings.h"

CommonParams::CommonParams()
    : nMaxLogSize( "common/max-log-size", 1048576, BoundsValidator<uint>( 100, 102400000 ) )
{
}

CommonParams& CommonConf()
{
    static CommonParams params;
    return params;
}
