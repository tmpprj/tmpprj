#ifndef _SEARCH_PARAMS_H_
#define _SEARCH_PARAMS_H_

#include <QtCore>
#include <settings.h>

struct SearchParams
{
    ConfParam< uint > stCharDetBlockSize;
    ConfParam< uint > nFileChunkSize;
    ConfParam< uint > nCheckerQueueSize;
    ConfParam< uint > nChunkOverlap;

    SearchParams();
};

SearchParams& SearchConf();

#endif

