#ifndef _PPT_H
#define _PPT_H 1

#include <stdio.h>
#include <math.h>
#include <boost/function.hpp>

void set_ppt_writer( boost::function< void ( unsigned short* ) > Func );
void do_ppt(FILE *input);

#endif /* _PPT_H */

