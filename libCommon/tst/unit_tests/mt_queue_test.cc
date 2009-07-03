#include <UnitTest++.h>

#include <mt_queue.hpp>
#include <iostream>

using namespace std;

TEST( mt_queue_Test1 )
{
    mt_queue< int > queue( 2 );

    queue.push( 1 );
    queue.push( 2 );
    queue.pop();
    queue.push( 3 );
    queue.clear();
}

