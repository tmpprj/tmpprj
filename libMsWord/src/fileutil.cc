#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "catdoc.h"
#include <unistd.h>
#include <QString>
#include <QFile>


/************************************************************************/
/* Searches for charset with given name and put pointer to malloced copy*/
/* of its name into first arg if found. Otherwise leaves first arg      */
/*  unchanged. Returns non-zero on success                              */
/************************************************************************/
int check_charset( char **filename,const char *charset )
{
    if ( !strncmp( charset,"utf-8",6 ) )
    {
        *filename=strdup( "utf-8" );
        return 1;
    }

    QFile file( ":/libmsword/charsets/" + QString( charset ) + ".txt" );
    if ( file.exists() )
    {
        *filename=strdup( charset );
        return 1;
    }
    return 0;
}

