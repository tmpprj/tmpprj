#include "search_conf.h"
#include "settings.h"

SearchParams::SearchParams()
    : stCharDetBlockSize( "search/charset-detect-block-size", "1024" ),
      nFileChunkSize( "search/file-chink-size", 1048576 ),
      nCheckerQueueSize( "search/checker-queue-size", 100 ),
      nChunkOverlap( "search/chunk-overlap", 100 )
{
}

SearchParams& SearchConf()
{
    static SearchParams params;
    return params;
}
