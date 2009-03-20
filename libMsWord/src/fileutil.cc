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
#ifdef __MSDOS__
	} else {
		strcpy(path_buf,add_exe_path(path_buf)); /* safe, becouse
													add_exe_path knows about PATH_BUF_SIZE */
#endif
	}
	return 1;

}	
/************************************************************************/
/* Searches for file name in specified list of directories. Sets        */
/* Returns dynamically allocated full path or NULL. if nothing          */
/* appropriate   Expects name to be dynamically allocated and frees it  */
/************************************************************************/
//char *find_file(char *name, const char *path)
//{ const char *p;
//	char *q;
//	char path_buf[PATH_BUF_SIZE];
//	char dir_sep[2]={DIR_SEP,0};
//	for (p=path;p;p=q+1) {
//		q=strchr(p,LIST_SEP);
//
//		if (q) {
//			if (!prepare_path_buf(path_buf,p,q)) continue;
//		} else {
//			q--;
//			if (!prepare_path_buf(path_buf,p,p+strlen(p))) continue;
//		}
//		strcat(path_buf,dir_sep); /* always one char */
//		if (strlen(path_buf)+strlen(name)>=PATH_BUF_SIZE)
//			continue; /* Ignore too deeply nested directories */
//		strcat(path_buf,name);
//		if (access(path_buf,0)==0) {
//			free(name);
//			return strdup(path_buf);
//		}
//	}
//	/* if we are here, nothing found */
//	free(name);
//	return NULL;
//}

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

    QFile file( ":/libmsword/charsets/" + QString(charset) + CHARSET_EXT );
    if( file.exists() )
    {
        *filename=strdup(charset);
		return 1;
	}
	return 0;
}

/**********************************************************************/
/*  Returns malloced string containing concatenation of two           */
/*  arguments                                                         */
/**********************************************************************/
char *stradd(const char *s1,const char *s2) 
{ char *res;
        res=(char*)malloc(strlen(s1)+strlen(s2)+1);
	if (!res) {
		fprintf (stderr,"Out of memory!");
		exit(1);
	}
	strcpy(res,s1);
	strcat(res,s2);
	return res;
}  
