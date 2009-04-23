/*
  Copyright 1998-2003 Victor Wagner
  Copyright 2003 Alex Ott
  This file is released under the GPL.  Details can be
  found in the file COPYING accompanying this distribution.
*/
#ifndef CATDOC_H
#define CATDOC_H


#include <stdio.h>
#include <ctype.h>
#include <boost/function.hpp>
#include "ole.h"


#ifndef SOURCE_CHARSET
#define SOURCE_CHARSET "cp1252"
#endif
#ifndef UNKNOWN_CHAR
#define UNKNOWN_CHAR "?"
#endif
/* Buffers for 32-bit and more program */
#define PARAGRAPH_BUFFER 262144
#define FILE_BUFFER 262144
#define PATH_BUF_SIZE 1024
/* Buffer for single line. Should be greater than wrap margin +
  longest substitution sequence */
#define LINE_BUF_SIZE 512
/*   Default value for wrap margin */
#ifndef WRAP_MARGIN
#define WRAP_MARGIN 72
#endif
/* variable (defined in catdoc.c) which holds actual value of wrap margin*/

extern  int wrap_margin;

/* Structure to store UNICODE -> target charset mappings */
/* array of 256 pointers (which may be null) to arrays of 256 short ints
   which contain 8-bit character codes or -1 if no matching char */
typedef short int  ** CHARSET;

extern short int *source_charset;
extern char bad_char[]; /* defines one-symbol string to replace unknown unicode chars */
extern char *source_csname;
extern int verbose; /* if true, some additional information would be
		       printed. defined in analyze.c */
extern int (*get_unicode_char)(FILE *f,long *offset,long fileend);
/* pointer to function which gets
                                     a char from stream */
extern int get_8bit_char (FILE *f,long *offset,long fileend);

extern int get_word8_char (FILE *f,long *offset,long fileend);

extern const char *charset_from_codepage(unsigned int codepage);
extern  short int *read_charset(const char *filename);

extern int to_unicode (short int *charset, int c) ;

void set_writer( boost::function< void ( unsigned short* ) > Func );

extern int signature_check;
extern int unknown_as_hex;

int check_charset(char **filename,const char *charset);
int process_file(FILE *f,long stop);
void output_paragraph(unsigned short int *buffer) ;
int parse_rtf(FILE *f);
/* format recognition*/
int analyze_format(FILE *f);
int parse_word_header(unsigned char *buffer,FILE *f,int offset,long curpos);
/* large buffers for file IO*/
extern char *input_buffer;
/* numeric conversions */
long int getlong(unsigned char *buffer,int offset);
unsigned long int getulong(unsigned char *buffer,int offset);
unsigned int getshort(unsigned char *buffer,int offset);
#endif
