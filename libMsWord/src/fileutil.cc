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
#include <sys/stat.h>
#include <stdlib.h>
#include "catdoc.h"
#include <unistd.h>
#if defined(MSDOS) && !defined(__MSDOS__)
#define __MSDOS__
#endif
#if defined(__MSDOS__) || defined(_WIN32)
//#include <dir.h>
//#include <dos.h>
#else
#include <glob.h>
#endif
#include <QString>
#include <QFile>


/************************************************************************/
/*  Copies component of string starting with p and ending one char      */
/*  before q into path_buf, expanding ~ if neccessary                   */
/************************************************************************/
int prepare_path_buf(char *path_buf, const char *start, const char *end) {
	if (*start == '~' && start[1] == DIR_SEP) {
		char *home=getenv("HOME");
		start++;
		if (!home) {
			if (end-start>PATH_BUF_SIZE) return 0;
			strncpy(path_buf,start,end-start);
			path_buf[end-start]=0;
		} else {
			int l = strlen(home);
			if (l+(end-start)>PATH_BUF_SIZE) return 0;
			strcpy(path_buf,home);
			strncpy(path_buf+l,start,end-start);
			path_buf[end-start+l]=0;
		}	
	} else {	
			if (end-start>PATH_BUF_SIZE) return 0;
			strncpy(path_buf,start,end-start);
			path_buf[end-start]=0;
	}
	/* Empty list element means current directory */
	if (!*path_buf) {
		path_buf[0]='.';
		path_buf[1]=0;
	}
	return 1;

}	


/************************************************************************/
/* Searches for charset with given name and put pointer to malloced copy*/
/* of its name into first arg if found. Otherwise leaves first arg      */
/*  unchanged. Returns non-zero on success                              */ 
/************************************************************************/
int check_charset(char **filename,const char *charset)
{
    if( !strncmp(charset,"utf-8",6) )
    {
		*filename=strdup("utf-8");
		return 1;
	}   

    QFile file( ":/libmsword/charsets/" + QString(charset) + ".txt" );
    if( file.exists() )
    {
        *filename=strdup(charset);
		return 1;
	}
	return 0;
}

