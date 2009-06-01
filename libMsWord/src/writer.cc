/*****************************************************************/
/* Output of unicode buffers with conversion into target encoding*/
/* And application of substitution maps                          */
/*                                                               */
/* This file is part of catdoc project                           */
/* (c) Victor Wagner 1996-2003, (c) Alex Ott 2003	             */
/*****************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "catdoc.h"
#include <boost/thread.hpp>

boost::function< void ( unsigned short* ) > WriterImpl;

void set_writer( boost::function< void ( unsigned short* ) > Func )
{
    WriterImpl = Func;
}

/************************************************************************/
/* Main output function.
 * Programs which read word-processor files should accumulate paragraphs
 * in the buffer as array of unicode 16-bit codes and pass to this
 * function
 ************************************************************************/
void output_paragraph( unsigned short int *buffer )
{
    boost::this_thread::interruption_point();
    if ( !WriterImpl.empty() )
        WriterImpl( buffer );
}

