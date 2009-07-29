/*
  Copyright 1998-2003 Victor Wagner
  Copyright 2003 Alex Ott
  This file is released under the GPL.  Details can be
  found in the file COPYING accompanying this distribution.
*/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "catdoc.h"
#include <QFile>
#include <QTextStream>
#include <log.h>
#include <QStringList>
#include <boost/concept_check.hpp>

char *source_csname=SOURCE_CHARSET;
short int * source_charset;
int unknown_as_hex=0;
char bad_char[]=UNKNOWN_CHAR;
/************************************************************************/
/* Converts char in input charset into unicode representation           */
/* Should be converted to macro                                         */
/************************************************************************/
int to_unicode( short int *charset, int c )
{
    return charset[c];
}

/************************************************************************/
/* Reads charset file (as got from ftp.unicode.org) and returns array of*/
/* 256 short ints (malloced) mapping from charset t unicode             */
/************************************************************************/
short int * read_charset( const char *filename )
{
    short int *pnew=( short int* )calloc( sizeof( short int ),256 );
    int c;
    long int uc;

    QFile file( ":/libmsword/charsets/" + QString( filename ) + ".txt" );
    if ( !file.exists() )
    {
        CLog(Debug) << "Cannot load charset " << filename << " - file not found";
        return NULL;
    }

    if ( !file.open( QIODevice::ReadOnly ) )
    {
        CLog(Debug) << "Cannot open file " << filename;
        return NULL;
    }

    for ( c=0;c<32;c++ )
        pnew[c]=c;

    QStringList strList;
    bool bConv1Ok, bConv2Ok;
    QTextStream stream( &file );
    while( !stream.atEnd() )
    {
        strList = stream.readLine().split( "\t", QString::SkipEmptyParts );

        if( strList.size() < 2 )
            continue;

        c = strList[0].toInt( &bConv1Ok, 16 );
        uc = strList[1].toLong( &bConv2Ok, 16 );

        if( QTextStream::Ok == stream.status() && bConv1Ok && bConv2Ok )
        {
            if ( c<0 || c>255 || uc<0 || ( uc>0xFEFE && uc!=0xFFFE ) )
            {
                CLog(Debug) << "Invalid charset file " << filename;
                return NULL;
            }
            pnew[c]=uc;
        }
    }
    return pnew;
}


/************************************************************************/
/* Reads 8-bit char and convers it from source charset                  */
/************************************************************************/

int get_8bit_char( FILE *f,long *offset,long fileend )
{
    boost::ignore_unused_variable_warning( fileend );
    unsigned char buf;
    if ( catdoc_read( &buf, 1, 1, f )==0 ) return EOF;
    ( *offset )++;
    return to_unicode( source_charset,buf );
}


struct cp_map
{
    int codepage;
    char *charset_name;
};


struct cp_map cp_to_charset [] =
{
    {
        10000,"mac-roman"
    },
    {10001,"mac-japanese"},
    {10002,"mac-tchinese"},
    {10003,"mac-korean"},
    {10004,"mac-arabic"},
    {10005,"mac-hebrew"},
    {10006,"mac-greek1"},
    {10007,"mac-cyrillic"},
    {10008,"mac-schinese"},
    {10010,"mac-romania"},
    {10017,"mac-ukraine"},
    {10021,"mac-thai"},
    {10029,"mac-centeuro"},
    {10079,"mac-iselandic"},
    {10081,"mac-turkish"},
    {10082,"mac-croatia"},
    {20866,"koi8-r"},
    {28591,"8859-1"},
    {28592,"8859-2"},
    {28593,"8859-3"},
    {28594,"8859-4"},
    {28595,"8859-5"},
    {28596,"8859-6"},
    {28597,"8859-7"},
    {28598,"8859-8"},
    {28599,"8859-9"},
    {28605,"8859-15"},
    {65001,"utf-8"},
    {0,NULL}
};

const char *charset_from_codepage( unsigned int codepage )
{

    static char buffer[7];
    struct cp_map *cp;
    if ( codepage==1200||codepage==1201 )
    {
        /* For UCS2 */
        return "";
    }
    else
        if ( codepage<10000 )
        {
            sprintf( buffer,"cp%d",codepage );
            return buffer;
        }
        else
        {
            for ( cp = cp_to_charset;cp->codepage!=0&& cp->codepage!=( int )codepage;cp++ );
            return cp->charset_name;
        }
}
