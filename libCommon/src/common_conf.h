#ifndef COMMON_CONF_H
#define COMMON_CONF_H

#include "settings.h"

struct CommonParams
{
    ConfParam< uint > nMaxLogSize;

    CommonParams();
};

CommonParams& CommonConf();

#endif
