/*
  Copyright 1996-2003 Victor Wagner
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
#include <unistd.h>
#include <ctype.h>
#include "catdoc.h"

void help(void);


int signature_check = 1;
int forced_charset = 0; /* Flag which disallow rtf parser override charset*/
int wrap_margin = WRAP_MARGIN;
int (*get_unicode_char)(FILE *f,long *offset,long fileend) =NULL;

char *input_buffer, *output_buffer;
/**************************************************************/
/*       Main program                                         */
/*  Processes options, reads charsets  files and substitution */
/*  maps and passes all remaining args to processfile         */
/**************************************************************/
int main(int argc, char **argv) {
	FILE *f;
	int c,i;
	char *tempname;
	short int *tmp_charset;
	int stdin_processed=0;
	input_buffer=malloc(FILE_BUFFER);
	if (!input_buffer) {
		fprintf(stderr,"Input buffer not allocated\n");
	}
	source_charset = read_charset(source_csname);
	if (!source_charset) exit(1);
	if (strncmp(dest_csname,"utf-8",6)) {
		tmp_charset = read_charset(dest_csname);
		if (!tmp_charset) exit(1);
		target_charset= make_reverse_map(tmp_charset);
		free(tmp_charset);
	} else {
		target_charset = NULL;
	}  

	set_std_func();
	c=0;
	f=fopen(argv[1],"rb");
	if (!f)
	{
		c=1;
		perror("catdoc");
		exit(0);
	}
	if (input_buffer) {
		if (setvbuf(f,input_buffer,_IOFBF,FILE_BUFFER)) {
			perror(argv[1]);
		}
	}
	c=analyze_format(f);
	fclose(f);
	return c;
}
/************************************************************************/
/* Displays  help message                                               */
/************************************************************************/
void help (void) {
	printf("Usage:\n catdoc [-vu8btawxlV] [-m number] [-s charset] "
			"[-d charset] [ -f format] files\n");
}
