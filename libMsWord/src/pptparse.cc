/**
 * @file   pptparse.c
 * @author Alex Ott <alexott@gmail.com>
 * @date   23 ����������������������������Ԝ���������������������������������������������������������Ԝ������������������������������������������������Ԝ�������������������� 2004
 * Version: $Id: pptparse.c,v 1.1.1.1 2006/02/24 17:44:06 vitus Exp $
 * Copyright: Alex Ott
 * 
 * @brief  .ppt parsing routines
 * 
 * 
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "ppt.h"
#include "catdoc.h"
#include "ppttypes.h"

static void process_item(int rectype, long reclen, int flags, FILE* input, int* iOffset, int* iLevel);

#if !defined(min)
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif


/** 
 * 
 * 
 * @param input 
 * @param filename 
 */
void do_ppt(FILE *input,char *filename) {
	int itemsread=1;
	int rectype;
	long reclen;
	int flags;
	unsigned char recbuf[8];
	int i;

	while(itemsread) 
	{
		int iOffset = 0;
        int iLevel = 0;

		itemsread = catdoc_read(recbuf, 1, 8, input);
/* 		fprintf(stdout,"itemsread=%d: ",itemsread); */
/* 		for(i=0; i<8; i++) */
/* 			fprintf(stdout,"%02x ",recbuf[i]); */
/* 		fprintf(stdout,"\n"); */
		
		if (catdoc_eof(input)) {
			process_item(DOCUMENT_END,0,0,input,&iOffset,&iLevel);
			return;
		}
		if(itemsread < 8)
			break;
		flags=(int)recbuf[0];
		rectype=getshort(recbuf,2);
		reclen=getulong(recbuf,4);
		if (reclen < 0) {
			return;
		}	

		process_item(rectype,reclen,flags,input,&iOffset,&iLevel);
	}
}


/** 
 * 
 * 
 * @param rectype 
 * @param reclen 
 * @param input 
 */
static void process_item (int rectype, long reclen, int flags, FILE* input, int* iOffset, int* iLevel ) 
{
    fprintf( stdout, "level=%d ", (*iLevel)++ );
    
	int i=0, u;
	static char buf[2];

	if( 0x0F == (0x0F&flags) && PROG_BINARY_TAG != rectype )
	{
        fprintf( stdout, "container type=%d, len=%d\n", rectype, reclen );

		int tmpitemsread=1;
		int tmprectype;
		long tmpreclen;
		int tmpflags;
		unsigned char recbuf[8];
		int i;
		int iTmpOffset=0;

		while( iTmpOffset < reclen )
		{
			tmpitemsread = catdoc_read(recbuf, 1, 8, input);
			fprintf(stdout,"itemsread=%d: ",tmpitemsread);
			for(i=0; i<8; i++)
				fprintf(stdout,"%02x ",recbuf[i]);
			fprintf(stdout,"\n");
		
			if( catdoc_eof(input) )
			{
                (*iLevel)--;
				return;
			}

			if( tmpitemsread < 8 )
				break;

			tmpflags=(int)recbuf[0];
			tmprectype=getshort(recbuf,2);
			tmpreclen=getulong(recbuf,4);


			if (reclen < 0) 
            {
                (*iLevel)--;
				return;
            }

			process_item( tmprectype, tmpreclen, tmpflags, input, &iTmpOffset, iLevel );
		}
		(*iOffset) += reclen;
        (*iLevel)--;
		return;
	}

	switch(rectype) 
	{
	case DOCUMENT_END:
		fprintf(stdout,"End of document, ended at %ld\n",catdoc_tell(input));
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case DOCUMENT:
		fprintf(stdout,"Start of document, reclen=%ld, started at %ld\n", reclen, catdoc_tell(input));
		//
		(*iOffset) += reclen;
		break;

	case DOCUMENT_ATOM:
		fprintf(stdout,"DocumentAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case SLIDE:
		fprintf(stdout,"Slide, reclen=%ld\n", reclen);
 		fputs("---------------------------------------\n",stdout);
//
		(*iOffset) += reclen;
		break;

	case SLIDE_ATOM:
		fprintf(stdout,"SlideAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;
		
	case SLIDE_BASE:
		fprintf(stdout,"SlideBase, reclen=%ld\n", reclen);
		//
		(*iOffset) += reclen;
		break;

	case SLIDE_BASE_ATOM:
		fprintf(stdout,"SlideBaseAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;
		
	case NOTES:
		fprintf(stdout,"Notes, reclen=%ld\n", reclen);
		//
		(*iOffset) += reclen;
		break;

	case NOTES_ATOM:
		fprintf(stdout,"NotesAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;
		
	case HEADERS_FOOTERS:
		fprintf(stdout,"HeadersFooters, reclen=%ld\n", reclen);
		//
		(*iOffset) += reclen;
		break;

	case HEADERS_FOOTERS_ATOM:
		fprintf(stdout,"HeadersFootersAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;
		
	case MAIN_MASTER:
		fprintf(stdout,"MainMaster, reclen=%ld\n", reclen);
		//
		(*iOffset) += reclen;
		break;
		
	case TEXT_BYTES_ATOM: 
	{
		fprintf(stdout,"TextBytes, reclen=%ld\n", reclen);
		for(i=0; i < reclen; i++) {
			catdoc_read(buf,1,1,input);
			if((unsigned char)*buf!=0x0d)
				fputs(convert_char((unsigned char)*buf),stdout);
			else
				fputc('\n',stdout);
		}
		fputc('\n',stdout);
		(*iOffset) += reclen;
	}
	break;
		
	case TEXT_CHARS_ATOM: 
	case CSTRING: 
	{
		long text_len;
			
		fprintf(stdout,"CString, reclen=%ld\n", reclen);
		text_len=reclen/2;
		for(i=0; i < text_len; i++) {
			catdoc_read(buf,2,1,input);
			u=(unsigned short)getshort(buf,0);
			if(u!=0x0d)
				fputs(convert_char(u),stdout);
			else
				fputc('\n',stdout);
		}
		fputc('\n',stdout);
		(*iOffset) += reclen;
	}
	break;
		
	case USER_EDIT_ATOM:
		fprintf(stdout,"UserEditAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case COLOR_SCHEME_ATOM:
		fprintf(stdout,"ColorSchemeAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case PPDRAWING:
		fprintf(stdout,"PPDrawing, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case ENVIRONMENT:
		fprintf(stdout,"Environment, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case SSDOC_INFO_ATOM:
		fprintf(stdout,"SSDocInfoAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case SSSLIDE_INFO_ATOM:
		fprintf(stdout,"SSSlideInfoAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case PROG_TAGS:
		fprintf(stdout,"ProgTags, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case PROG_STRING_TAG:
		fprintf(stdout,"ProgStringTag, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case PROG_BINARY_TAG:
		fprintf(stdout,"ProgBinaryTag, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case LIST:
		fprintf(stdout,"List, reclen=%ld\n", reclen);
		//
		(*iOffset) += reclen;
		break;

	case SLIDE_LIST_WITH_TEXT:
		fprintf(stdout,"SlideListWithText, reclen=%ld\n", reclen);
 		fputs("---------------------------------------\n",stdout);
		//
		(*iOffset) += reclen;
		break;

	case PERSIST_PTR_INCREMENTAL_BLOCK:
		fprintf(stdout,"PersistPtrIncrementalBlock, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case EX_OLE_OBJ_STG:
		fprintf(stdout,"ExOleObjStg, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case PPDRAWING_GROUP:
		fprintf(stdout,"PpdrawingGroup, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case EX_OBJ_LIST:
		fprintf(stdout,"ExObjList, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case TX_MASTER_STYLE_ATOM:
		fprintf(stdout,"TxMasterStyleAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case HANDOUT:
		fprintf(stdout,"Handout, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case SLIDE_PERSIST_ATOM:
		fprintf(stdout,"SlidePersistAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case TEXT_HEADER_ATOM:
		fprintf(stdout,"TextHeaderAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case TEXT_SPEC_INFO:
		fprintf(stdout,"TextSpecInfo, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

	case STYLE_TEXT_PROP_ATOM:
		fprintf(stdout,"StyleTextPropAtom, reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;
		break;

		/*	case :
		fprintf(stdout,", reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		break;*/

		/*	case :
		fprintf(stdout,", reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		break;*/

	default:
		fprintf(stdout,"Default action for rectype=%d reclen=%ld\n",
						rectype, reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		(*iOffset) += reclen;

	}
    (*iLevel)--;
}
