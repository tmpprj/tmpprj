/*****************************************************************/
/* Reading routines for MS-Word, MS-Write and text files         */
/*                                                               */
/* This file is part of catdoc project                           */
/* (c) Victor Wagner 1996-2003, (c) Alex Ott 2003	             */
/*****************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <string.h>
#include <stdio.h>
#include "catdoc.h"
#include <boost/thread.hpp>

unsigned short int buffer[PARAGRAPH_BUFFER];
static unsigned char read_buf[256];
static int buf_is_unicode;

/**************************************************************************/
/*  process_file - main process engine. Reads word file using function,   */
/*  pointed by get_unicode_char, searches for things which looks like     */
/*  paragraphs and print them out                                         */
/**************************************************************************/
int process_file( FILE *f,long stop )
{
    int bufptr;
    int tabmode=0;
    long offset=0;
    int hyperlink_mode = 0;
    unsigned short c;
    /* Now we are starting to read with get_unicode_char */
    while ( !catdoc_eof( f ) && offset<stop )
    {
        bufptr = -1;
        do
        {
            boost::this_thread::interruption_point();
            c=get_unicode_char( f,&offset,stop );
            /* Following symbols below 32 are allowed inside paragraph:
               0x0002 - footnote mark
               0x0007 - table separator (converted to tabmode)
               0x0009 - Horizontal tab ( printed as is)
               0x000B - hard return
               0x000C - page break
               0x000D - return - marks an end of paragraph
               0x001E - IS2 for some reason means short defis in Word.
               0x001F - soft hyphen in Word
               0x0013 - start embedded hyperlink
               0x0014 - separate hyperlink URL from text
               0x0015 - end embedded hyperlink
               */
            if ( tabmode )
            {
                tabmode=0;
                if ( c==0x007 )
                {
                    buffer[++bufptr]=0x1E;
                    continue;
                }
                else
                {
                    buffer[++bufptr]=0x1C;
                }
            }
            if ( c<32 )
            {
                switch ( c )
                {
                case 0x007:
                    tabmode = 1;
                    break;
                case 0x000D:
                case 0x000B:
                    buffer[++bufptr]=0x000A;
                    break;
                case 0x000C:
                    buffer[++bufptr]=c;
                    break;
                case 0x001E:
                    buffer[++bufptr]='-';
                    break;
                case 0x0002:
                    break;

                case 0x001F:
                    buffer[++bufptr]=0xAD;/* translate to Unicode
														  soft hyphen */
                    break;
                case 0x0009:
                    buffer[++bufptr]=c;
                    break;
                case 0x0013:
                    hyperlink_mode=1;
                    buffer[++bufptr]=' ';
                    break;
                case 0x0014:
                    hyperlink_mode = 0;
                    /*fall through */
                case 0x0015:
                    /* just treat hyperlink separators as
                     * space */
                    buffer[++bufptr]=' ';
                    break;
                case 0x0001:
//TODO:
//                    if ( hyperlink_mode )
                        break;
                    /* else fall through */
                default:
                    bufptr=-1; /* Any other control char - discard para*/
                }
            }
            else if ( c != 0xfeff )
            {
                /* skip ZERO-WIDTH-UNBREAKABLE-SPACE. Output anything
                 * else*/
                buffer[++bufptr]=c;
            }
        }
        while ( bufptr<PARAGRAPH_BUFFER-2 &&
                !catdoc_eof( f ) &&
                buffer[bufptr]!=0x000a );
        if ( bufptr>0 )
        {
            buffer[++bufptr]=0;
            output_paragraph( buffer );
        }
    }
    return 0;
}
/**********************************************************************/
/* Reads file from MS-Word 97 and above file. Takes in account strange*
 * situation that unicode and non-unicode 256-byte blocks could be    *
 * intermixed in word file                                            *
 *                                                                    *
 * Parameters:                                                        *
 *                                                                    *
 * f - file to read                                                   *
 * offset - position of the character inside file (to determine       *
 * possible  block boundaries                                         *
 **********************************************************************/
int get_word8_char( FILE *f,long *offset,long fileend )
{
    int count,i,u;
    char c;
    if (( i=( *offset )%256 ) ==0 )
    {
        count=catdoc_read( read_buf,1,256,f );
        memset( read_buf+count,0,256-count );
        buf_is_unicode=0;
        if ( *offset+( long )count>fileend )
        {
            count=fileend-*offset;
        }
        while ( i<count )
        {
            c=read_buf[i++];
            if (( c==0x20|| c==0x0D||ispunct(( unsigned char )c ) )&&i<count&&read_buf[i]==0 )
            {
                buf_is_unicode=1;
                break;
            }
            i++;
        }
        i=0;
    }
    if ( buf_is_unicode )
    {
        u=read_buf[i] | read_buf[i+1]<<8;
        ( *offset )+=2;
    }
    else
    {
        u=to_unicode( source_charset,read_buf[i] );
        ( *offset )++;
    }
    return u;
}


