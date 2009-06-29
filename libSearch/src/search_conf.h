#ifndef _SEARCH_PARAMS_H_
#define _SEARCH_PARAMS_H_

#include <QtCore>
#include <settings.h>

struct SearchParams
{
    ConfParam< size_t > stCharDetBlockSize;

    SearchParams();
};

SearchParams& SearchConf();

#endif

