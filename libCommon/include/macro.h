#ifndef MACRO_H
#define MACRO_H

#include <boost/typeof/typeof.hpp>

#define FOREACH( varname, container ) \
        for( BOOST_TYPEOF( ( container ).begin() ) varname = ( container ).begin(); \
                varname != ( container ).end(); varname++ )

#endif
