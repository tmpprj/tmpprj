//========================================================================
//
// Error.cc
//
// Copyright 1996-2003 Glyph & Cog, LLC
//
//========================================================================

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma implementation
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include "GlobalParams.h"
#include "Error.h"
#include "log.h"

void CDECL error(int pos, char *msg, ...) {
    va_list args;

    // NB: this can be called before the globalParams object is created
    if (globalParams.get() && globalParams->getErrQuiet()) {
        return;
    }
    CLog(debug,true) << "libPdf::error: ";
    if (pos >= 0)
        CLog(debug,true) << "(" << pos << "):";

    char buf[1024];
    va_start(args, msg);
    vsnprintf(buf, sizeof(buf), msg, args);
    va_end(args);
    CLog(debug) << buf;
}
