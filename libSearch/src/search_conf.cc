#include "search_conf.h"
#include "settings.h"

SearchParams::SearchParams()
    : stCharDetBlockSize( "search/charset-detect-block-size", "1024", BoundsValidator<uint>( 1, 10240000 ) ),
      nFileChunkSize( "search/file-chunk-size", 1048576, BoundsValidator<uint>( 100, 10240000 ) ),
      nCheckerQueueSize( "search/checker-queue-size", 100, BoundsValidator<uint>( 1, 1000 )  ),
      nChunkOverlap( "search/chunk-overlap", 100, BoundsValidator<uint>( 0, 2000 ) )
{
}

SearchParams& SearchConf()
{
    static SearchParams params;
    return params;
}
