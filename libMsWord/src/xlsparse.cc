#include <stdlib.h>
#include <string.h>
#include "xls.h"
#include "catdoc.h"
#include "xltypes.h"
#include "float.h"
#include <math.h>
#include <time.h>
#ifndef HAVE_STRFTIME
#include "strftime.h"
#endif
#include <boost/concept_check.hpp>
#include "log.hpp"
#include <macro.h>
#include <map>

static unsigned char rec[MAX_MS_RECSIZE];
int biff_version=0;
short int *formatTable=NULL;
char *forced_date_format = NULL;
size_t formatTableIndex = 0;
size_t formatTableSize = 0;
double date_shift = 25569.0;
#define FLT_FORMAT(a,b,c) a #b c
#define MK_FORMAT(x) FLT_FORMAT("%.",x,"g")
char number_format[8]=MK_FORMAT( DBL_DIG );

const char* cCharsetMap[256] = { "cp1252", "cp1252", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "mac-roman", NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 "cp932", "cp949", "johab", NULL, NULL, NULL, "cp936", NULL, "cp950", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, "cp1253", "cp1254", "cp1258", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, "cp1255", "cp1256", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "cp1257", NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "cp1251", NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "cp874", NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "cp1250", NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "cp850" };

void CleanUpFormatIdxUsed( void );

void do_table( FILE *input )
{
    std::vector<unsigned int> vecFontsCharsets;
    std::vector<unsigned int> vecXfFonts;
    long rectype;
    long reclen,offset=0;
    int eof_flag=0;
    int itemsread=1;
    date_shift=25569.0; /* Windows 1900 date system */
    CleanUpFormatIdxUsed();
    while ( itemsread )
    {
        catdoc_read( rec,2,1,input );
        biff_version=getshort(( unsigned char* )rec,0 );
        catdoc_read( rec,2,1,input );
        reclen=getshort(( unsigned char* )rec,0 );
        if ( biff_version == 0x0809 || biff_version == 0x0409 ||
                biff_version == 0x0209 || biff_version == 0x0009 )
        {
            if ( reclen==8 || reclen==16 )
            {
                if ( biff_version == 0x0809 )
                {
                    itemsread=catdoc_read( rec,4,1,input );
                    //build_year=getshort(( unsigned char* )rec+2,0 );
                    //build_rel=getshort(( unsigned char* )rec,0 );
                    CLog(debug) << "ver=" << std::hex << getshort( (unsigned char*)rec,0 );
                    unsigned short usVer = getshort( (unsigned char*)rec,0 );
                    if( 0x600 == usVer )
                    //CLog() << debug << "y = " << hex << build_year << " r = " << build_rel;
//                    if ( build_year > 5 )
                    {
                        itemsread=catdoc_read( rec,8,1,input );
                        biff_version=8;
                        offset=12;
                    }
                    else if( 0x500 == usVer )
                    {
//                        throw std::runtime_error( "XLS: Unsupported file format" );
                        biff_version=7;
                        offset=4;
                    }
                    else
                        throw std::runtime_error( "XLS: Unsupported file format" );
                }
                else if ( biff_version == 0x0209 )
                {
                    throw std::runtime_error( "XLS: Unsupported file format" );
                    //                    biff_version=3;
                    //                    offset=2;
                }
                else if ( biff_version == 0x0409 )
                {
                    throw std::runtime_error( "XLS: Unsupported file format" );
//                    offset=2;
//                    biff_version=4;
                }
                else
                {
                    throw std::runtime_error( "XLS: Unsupported file format" );
//                    biff_version=2;
                }
                itemsread=catdoc_read( rec,reclen-offset,1,input );
                break;
            }
            else
            {
                CLog(debug) << ": Invalid BOF record";
                return;
            }
        }
        else
        {
            itemsread=catdoc_read( rec,126,1,input );
        }
    }

    if ( catdoc_eof( input ) )
    {
        CLog(debug) << ": No BOF record found";
        throw std::runtime_error( "ExtractXls: incorrect file format" );
    }
    while( itemsread )
    {
        unsigned char buffer[2];
        rectype = 0;
        itemsread = catdoc_read( buffer, 2, 1, input );
        if ( catdoc_eof( input ) )
        {
            process_item( MSEOF,0,NULL, vecFontsCharsets, vecXfFonts );
            return;
        }

        rectype=getshort(( unsigned char* )buffer,0 );
        if ( itemsread == 0 )
            break;
        reclen=0;

        itemsread = catdoc_read( buffer, 2, 1, input );
        reclen=getshort( buffer,0 );
        if ( reclen && reclen <MAX_MS_RECSIZE &&reclen >0 )
        {
            itemsread = catdoc_read( rec, 1, reclen, input );
            rec[reclen] = '\0';
        }
        if ( eof_flag )
        {
            if ( rectype != BOF )
            {
                break;
            }
        }
        /* 		fprintf(stderr,"Rectype 0x%04X reclen=%d\n",rectype, reclen); */
        if( !process_item( rectype, reclen, (char*)rec, vecFontsCharsets, vecXfFonts ) )
            break;
        if ( rectype == MSEOF )
        {
            eof_flag=1;
        }
        else
        {
            eof_flag=0;
        }
    }
    return;
}
unsigned char **sst=NULL;/* Shared string table parsed into array of strings in
                                                        output encoding*/
int sstsize = 0; /*Number of strings in SST*/
unsigned char *sstBuffer=NULL; /*Unparsed sst to accumulate all its parts*/
int sstBytes = 0; /*Size of SST Data, already accumulated in the buffer */
int codepage=1251; /*default*/
int prev_rectype=0;
/* holds a pointer to formula value, becouse value itself would be in
 * next biff record
 */
unsigned char **saved_reference = NULL;

bool process_item( int rectype, int reclen, char *rec, std::vector<unsigned int>& vecFontCharsets, std::vector<unsigned int>& vecXfFonts )
{
    if ( rectype != CONTINUE && prev_rectype == SST )
    {
        /* we have accumulated  unparsed SST, and now encountered
         * another record, which indicates that SST is ended */
        /* fprintf(stderr,"parse sst!\n");*/
        if( !parse_sst(( char* )sstBuffer,sstBytes ) )
            return false;
    }
    switch ( rectype )
    {
    case FILEPASS:
        throw std::runtime_error( "ExtractXls: file is encrypted" );
    case WRITEPROT:
        throw std::runtime_error( "ExtractXls: file is protected" );

    case 0x42:
    {
        if ( source_charset ) break;
        codepage=getshort(( unsigned char* )rec,0 );
        /*fprintf(stderr,"CODEPAGE %d\n",codepage); */
        if ( codepage!=1200 )
        {
            const char *cp = charset_from_codepage( codepage );
            source_charset=read_charset( cp );
        }
        break;
    }
    case FORMAT:
    {
        int format_code;
        format_code=getshort(( unsigned char* )rec,0 );
        SetFormatIdxUsed( format_code );
        /* this debug code prints format string */
        /*
        int i;
        char *ptr;
//        fprintf(stderr,"Format %x \"",format_code);
        if (rec[2] == reclen - 3 && rec[3] != 0) {
        for (i=0,ptr=rec+3;i<rec[2];i++,ptr++) {
//        fputc(*ptr,stderr);
        }
        } else {
        for (i=0,ptr=rec+5;i<rec[2];i++,ptr+=2) {
//        fputc(*ptr,stderr);
        }
        }
//        fprintf (stderr,"\"\n");
        */
        break;
    }
    case SST:
    {
        /* Just copy SST into buffer, and wait until we get
        * all CONTINUE records
        */
        /* 		fprintf(stderr,"SST\n"); */
        /* If exists first SST entry, then just drop it and start new*/
        if ( sstBuffer != NULL )
            free( sstBuffer );
        if ( sst != NULL )
            free( sst );

        sstBuffer=( unsigned char* )malloc( reclen );
        sstBytes = reclen;
        if ( sstBuffer == NULL )
            throw std::runtime_error( "ExtractXls: not enough memory" );
        memcpy( sstBuffer,rec,reclen );
        break;
    }
    case CONTINUE:
    {
        if ( prev_rectype != SST )
        {
            return true; /* to avoid changing of prev_rectype;*/
        }
        sstBuffer=( unsigned char* )realloc( sstBuffer,sstBytes+reclen );
        if ( sstBuffer == NULL )
            throw std::runtime_error( "ExtractXls: not enough memory" );
        memcpy( sstBuffer+sstBytes,rec,reclen );
        sstBytes+=reclen;
        return true;
    }
    case LABEL:
    {
        int row,col;
        unsigned char **pcell;
        unsigned char *src=( unsigned char * )rec+6;

        saved_reference=NULL;
        row = getshort(( unsigned char* )rec,0 );
        col = getshort(( unsigned char* )rec,2 );
        int iXfIndex = getshort( (unsigned char*)rec, 4 );
        //fprintf(stderr,"LABEL!xf=%d\n", iXfIndex );
        pcell=allocate( row,col );

        bool bEndFlag;
        if( iXfIndex < (int)vecXfFonts.size() && vecXfFonts[iXfIndex] > 0 && vecXfFonts[iXfIndex]-1 < vecFontCharsets.size() && vecFontCharsets[vecXfFonts[iXfIndex]-1] < 256 )
            *pcell=( unsigned char* )copy_unicode_string( &src, bEndFlag, cCharsetMap[ vecFontCharsets[ vecXfFonts[iXfIndex]-1 ] ] );
        else
            *pcell=( unsigned char* )copy_unicode_string( &src, bEndFlag );

        if( !bEndFlag )
            return false;
        break;
    }
    case BLANK:
    {
        int row,col;
        unsigned char **pcell;
        row = getshort(( unsigned char* )rec,0 );
        col = getshort(( unsigned char* )rec,2 );
        pcell=allocate( row,col );
        *pcell=NULL;
        break;
    }
    case MULBLANK:
    {
        int row, startcol,endcol;
        unsigned char **pcell;
        row = getshort(( unsigned char* )rec,0 );
        startcol = getshort(( unsigned char* )rec,2 );
        endcol=getshort(( unsigned char* )rec,reclen-2 );
        pcell=allocate( row,endcol );
        *pcell=NULL;
        break;
    }
    case CONSTANT_STRING:
    {
        //SST is always unicode, and get from copy_unicode_string while parsing sst table
//        int row = getshort(( unsigned char* )rec,0 );
//        int col = getshort(( unsigned char* )rec,2 );
//        short int* pCharset = NULL;
//        unsigned int iXfIndex = getshort( (unsigned char*)rec,4 );
//
//        unsigned char **pcell;
//        int string_no=getshort(( unsigned char* )rec,6 );
//        if ( !sst )
//        {
//            CLog() << debug << "CONSTANT_STRING before SST parsed";
//            exit( 1 );
//        }
//        /* 									fprintf(stderr,"col=%d row=%d no=%d\n",col,row,string_no); */
//
//        saved_reference=NULL;
//        pcell=allocate( row,col );
//        if ( string_no>=sstsize|| string_no < 0 )
//        {
//            CLog() << debug << "string index out of boundary";
//            exit( 1 );
//        }
//        else if ( sst[string_no] !=NULL )
//        {
//            int len;
//            char *outptr;
//            len=strlen(( const char* )sst[string_no] );
//            *pcell=( unsigned char* )malloc( len+1 );
//            outptr=( char* )( *pcell );
//            strcpy( outptr,( const char* )sst[string_no] );
//        }
//        else
//        {
//            *pcell=( unsigned char* )malloc( 1 );
//            strcpy(( char* )*pcell,"" );
//        }
        break;
    }
    case 0x03:
    case 0x103:
    case 0x303:
    case NUMBER:
    {
        int row,col;
        unsigned char **pcell;

        saved_reference=NULL;
        row = getshort(( unsigned char* )rec,0 )-startrow;
        col = getshort(( unsigned char* )rec,2 );
        pcell=allocate( row,col );
        *pcell=( unsigned char* )strdup( format_double( rec,6,getshort(( unsigned char* )rec,4 ) ) );
        break;
    }
    case INTEGER_CELL:
    {
        int row,col;
        unsigned char **pcell;

        row = getshort(( unsigned char* )rec,0 )-startrow;
        col = getshort(( unsigned char* )rec,2 );
        pcell=allocate( row,col );
        *pcell=( unsigned char* )strdup( format_int( getshort(( unsigned char* )rec,7 ),getshort(( unsigned char* )rec,4 ) ) );
        break;

    }
    case RK:
    {
        int row,col,format_code;
        unsigned char **pcell;

        saved_reference=NULL;
        row = getshort(( unsigned char* )rec,0 )-startrow;
        col = getshort(( unsigned char* )rec,2 );
        pcell=allocate( row,col );
        format_code = getshort(( unsigned char* )rec,4 );
        *pcell=( unsigned char* )strdup( format_rk( rec+6,format_code ) );
        break;
    }
    case MULRK:
    {
        int row,col,startcol,endcol,offset,format_code;
        unsigned char **pcell;
        row = getshort(( unsigned char* )rec,0 )-startrow;
        startcol = getshort(( unsigned char* )rec,2 );
        endcol = getshort(( unsigned char* )rec,reclen-2 );
        saved_reference=NULL;

        for ( offset=4,col=startcol;col<=endcol;offset+=6,col++ )
        {
            pcell=allocate( row,col );
            format_code=getshort(( unsigned char* )rec,offset );
            *pcell=( unsigned char* )strdup( format_rk( rec+offset+2,format_code ) );

        }
        break;
    }
    case FORMULA:
    {
        int row,col;
        unsigned char **pcell;
        saved_reference=NULL;
        row = getshort(( unsigned char* )rec,0 )-startrow;
        col = getshort(( unsigned char* )rec,2 );
        pcell=allocate( row,col );
        if ((( unsigned char )rec[12]==0xFF )&&( unsigned char )rec[13]==0xFF )
        {
            /* not a floating point value */
            if ( rec[6]==1 )
            {
                /*boolean*/
                char buf[2]="0";
                buf[0]+=rec[9];
                *pcell=( unsigned char* )strdup( buf );
            }
            else if ( rec[6]==2 )
            {
                /*error*/
                char buf[6]="ERROR";
                *pcell=( unsigned char* )strdup( buf );
            }
            else if ( rec[6]==0 )
            {
                saved_reference=pcell;
            }
        }
        else
        {
            int format_code=getshort(( unsigned char* )rec,4 );
            *pcell=( unsigned char* )strdup( format_double( rec,6,format_code ) );
        }
        break;
    }
    case STRING:
    {
        unsigned char *src=( unsigned char * )rec;
        if ( !saved_reference )
        {
            CLog(debug) << "String record without preceeding string formula";
            break;
        }
        CLog(debug) << "String";
        bool bEndFlag;
        *saved_reference=( unsigned char* )copy_unicode_string( &src, bEndFlag );
        if( !bEndFlag )
            return false;
        break;
    }
    case BOF:
    {
        if ( rowptr )
        {
            CLog(debug) << "BOF when current sheet is not flushed";
            free_sheet();
        }
        break;
    }
    case FONT2:
    {
//        CLog() << debug << "FONT: " << hex << (unsigned int)(unsigned char)rec[12];
        vecFontCharsets.push_back( (unsigned char)rec[12] );
    }break;
    case XF:
    case 0x43: /*from perl module Spreadsheet::ParseExecel */
    {
        vecXfFonts.push_back( getshort( (unsigned char*)rec, 0 ) );
        short int formatIndex = getshort( ( unsigned char* )rec,2 );
        /* we are interested only in format index here */
        if ( formatTableIndex >= formatTableSize )
        {
            formatTable=( short int* )realloc( formatTable, ( formatTableSize+=16 )*sizeof( short int ) );

            if ( !formatTable )
                throw std::runtime_error( "ExtractXls: not enough memory" );        }
        formatTable[formatTableIndex++] = formatIndex;
        break;
    }
    case MS1904: /* Macintosh 1904 date system */
        date_shift=24107.0;
        break;


    case MSEOF:
    {
        if ( !rowptr ) break;
        print_sheet();
        free_sheet();
        break;
    }
    case ROW:
    {
        /*  		fprintf(stderr,"Row! %d %d %d\n",getshort((unsigned char*)rec,0), getshort((unsigned char*)rec+2,0),getshort((unsigned char*)rec+4,0));  */
        break;
    }
    case INDEX:
    {
        /* 		fprintf(stderr,"INDEX! %d %d\n", getlong(rec+4,0), getlong(rec+8,0));  */
        break;
    }
    }
    prev_rectype=rectype;

    return true;
}

boost::function< bool ( unsigned short* ) > XlsWriterImpl;

void set_xls_writer( boost::function< bool ( unsigned short* ) > Func )
{
    XlsWriterImpl = Func;
}


class CCharsetCache
{
public:

    ~CCharsetCache()
        {
            FOREACH( it, m_mapCharsets )
                ::free( it->second );
        }


    short int* GetCharset( const char* strCharsetName )
        {
            if( NULL == strCharsetName )
                return NULL;

            std::map<std::string, short int*>::iterator It;
            if( m_mapCharsets.end() != ( It = m_mapCharsets.find( std::string(strCharsetName) ) ) )
                return It->second;

            char* strFileName;
            check_charset( &strFileName, strCharsetName );
            short int* Charset = read_charset( strFileName );
            ::free( strFileName );
            m_mapCharsets[ std::string( strCharsetName ) ] = Charset;
            return Charset;
        }

private:

    std::map<std::string, short int*> m_mapCharsets;

};



/*
 * Extracts string from sst and returns mallocked copy of it
 */
char *copy_unicode_string( unsigned char **src, bool& bEndFlag, const char* strCharsetName )
{
    int count=0;
    int flags = 0;
    int start_offset=0;
    int to_skip=0;
                  
    int offset = 1;
    int charsize;
    /* 	char *realstart=*src; */
    char *dest;		
    unsigned char *s = NULL;
    char *d = NULL,*c = NULL;

    int i,u,l,len;

    /* 	for(i=0;i<20;i++) */
    /* 		fprintf(stderr,"%02x ",(*src)[i]); */
    /* 	fprintf(stderr,"\n"); */

    bEndFlag = true;

    flags = *( *src+1+offset );
    if ( !( flags == 0 || flags == 1 || flags == 8 || flags == 9 ||
            flags == 4 || flags == 5 || flags == 0x0c || flags == 0x0d ) )
    {
        count=**src;
        flags = *( *src+offset );
        offset --;
        flags = *( *src+1+offset );
        if ( !( flags == 0 || flags == 1 || flags == 8 || flags == 9 ||
                flags == 4 || flags == 5 || flags == 0x0c || flags == 0x0d ) )
        {
            /* 			fprintf(stderr,"Strange flags = %d, returning NULL\n", flags); */
            return NULL;
        }
    }
    else
    {
        count=getshort( *src,0 );
    }
    charsize=( flags &0x01 ) ? 2 : 1;


    switch ( flags & 12 )
    {
    case 0x0c: /* Far East with RichText formating */
        to_skip=4*getshort( *src,2+offset )+getlong( *src, 4+offset );
        start_offset=2+offset+2+4;
        /* 		fprintf(stderr,"Far East with RichText formating\n"); */
        break;

    case 0x08: /* With RichText formating */
        to_skip=4*getshort( *src,2+offset );
        start_offset=2+offset+2;
        /* 		fprintf(stderr,"With RichText formating %d\n",getshort(*src,2+offset)); */
        break;

    case 0x04: /* Far East */
        to_skip=getlong( *src, 2+offset );
        start_offset=2+offset+4;
        /* 		fprintf(stderr,"Far East\n"); */
        break;

    default:
        to_skip=0;
        start_offset=2+offset;
        /* 		fprintf(stderr,"Default string\n"); */
    }

    /* 	fprintf(stderr,"count=%d skip=%d start_offset=%d\n", */
    /* 					count, to_skip, start_offset); */
    if (( dest=( char* )malloc( count+1 ) ) == NULL )
        throw std::runtime_error( "MsWord::ExtractXls: not enough memory" );
    *src+=start_offset;
    len = count;
    *dest=0;
    l=0;


    static CCharsetCache cache;
    short int* Charset;
    if( NULL != strCharsetName )
        Charset = cache.GetCharset( strCharsetName );
    else if( !source_charset )
    {
        check_charset( &source_csname,source_csname );
        /* fprintf(stderr,"charset=%s\n",source_csname);*/
        source_charset=read_charset( source_csname );
    }


    std::vector<unsigned short> vecUString;
    for ( s=( unsigned char* )*src,d=dest,i=0;i<count;i++,s+=charsize )
    {
        /* 		fprintf(stderr,"l=%d len=%d count=%d charsize=%d\n",l,len,count,charsize); */
        if (( charsize == 1 && ( *s == 1 || *s == 0 ) ) ||
                ( charsize == 2 && ( *s == 1 || *s == 0 ) && *( s+1 ) != 4 ) )
        {
            /* 			fprintf(stderr,"extchar (unicode)=%02x %02x\n",*s, *(s+1)); */
            charsize=( *s &0x01 ) ? 2 : 1;
            if ( charsize == 2 )
                s-=1;
            count++;
            continue;
        }
        if ( charsize == 2 )
        {
            u=( unsigned short )getshort(( unsigned char* )s,0 );
            vecUString.push_back(u);
            //TODO:
            //c=convert_char(u);
            /* 			fprintf(stderr,"char=%02x %02x\n", *s, *(s+1)); */
        }
        else
        {
            if( NULL != strCharsetName )
                u=( unsigned short )to_unicode( Charset,( unsigned char )*s );
            else if( !source_charset )
                u=( unsigned short )to_unicode( source_charset,( unsigned char )*s );
            else
                u=( unsigned short )to_unicode( source_charset,( unsigned char )*s );
            vecUString.push_back(u);
            //TODO:
            //c=convert_char(u);
        }
        if ( c != NULL )
        {
            int dl = strlen( c );
            while ( l+dl>=len )
            {
                len+=16;
                dest=( char* )realloc( dest,len+1 );
            }
            d=dest+l;
            strcpy( d,c );
            d+=dl;
            l+=dl;
        }
    }


    vecUString.push_back(0);
    if ( !XlsWriterImpl.empty() )
    {
        if( !XlsWriterImpl( &vecUString[0] ) )
            bEndFlag = false;
        vecUString.clear();
    }

    *src=( unsigned char* )s+to_skip;

    return dest;
}


/*
 * Format code is index into format table (which is list of XF records
 * in the file
 * Second word of XF record is format type idnex
 * format index between 0x0E and 0x16 also between 0x2D and ox2F denotes
 * date if it is not used for explicitly stored formats.
 * BuiltInDateFormatIdx converts format index into index of explicit
 * built-in date formats sutable for strftime.
 */
int BuiltInDateFormatIdx( int index )
{
    int offset;
    offset=1; /* offset of date formats */
    /* 0 is used as false -- format not found */
    if (( index>= 0x0E ) && ( index<=0x16 ) )
    {
        return offset+index-0x0E;
    }
    else
        if (( index>=0x2d ) && ( index<=0x2F ) )
        {
            return offset+index-0x2d+9;
        }
        else if ( index==0xa4 )
        {
            return 12+offset;
        }
        else
            return 0;
}

/*
 * GetBuiltInDateFormat stores and returns
 * built in xls2csv strftime formats.
 */
#define NUMOFDATEFORMATS 13
char *GetBuiltInDateFormat( int dateindex )
{
    static char *formats[]=
    {
        /* reserved  */ NULL, /* BuiltInDateFormatIdx use dateindex=0 as flag format not found */
        /* 0x0E */ "%m-%d-%y",		/* 01 */
        /* 0x0F */ "%d-%b-%y",		/* 02 */
        /* 0x10 */ "%d-%b",		/* 03 */
        /* 0x11 */ "%b-%d",	 	/* 04 */
        /* 0x12 */ "%l:%M %p",		/* 05 */
        /* 0x13 */ "%l:%M:%S %p",		/* 06 */
        /* 0x14 */ "%H:%M",		/* 07 */
        /* 0x15 */ "%H:%M:%S",		/* 08 */
        /* 0x16 */ "%m-%d-%y %H:%M",	/* 09 */
        /* 0x2d */ "%M:%S",		/* 10 */
        /* 0x2e */ "%H:%M:%S",		/* 11 */
        /* 0x2f */ "%M:%S",		/* 12 */
        /* 0xa4 */ "%m.%d.%Y %l:%M:%S %p"	/* 13 */
    };
    if ( dateindex>0 && dateindex <= NUMOFDATEFORMATS )
    {
        return formats[dateindex];
    }
    else
        return NULL;
}

static char FormatIdxUsed[NUMOFDATEFORMATS];

void CleanUpFormatIdxUsed()
{
    int i;
    for ( i=0;i<NUMOFDATEFORMATS; i++ );
    FormatIdxUsed[i]=0;
}

/*
 * format index between 0x0E and 0x16 also between 0x2D and ox2F denotes
 * date in case when they are built-in Excel97 formats.
 * Nevertheless, those indexes can be used for explicitly stored formats,
 * which are not dates in general.
 * SetFormatIdxUsed marks this formats as already used
 * and excludes them from list of built-in formats
 * preventing misformatting of corresponding data.
 */
void SetFormatIdxUsed( int format_code )
{
    int dateindex;
    /*fprintf(stderr,"Format idx %x to be set to dirty\n",format_code);
     */
    dateindex=BuiltInDateFormatIdx( format_code );
    if ( dateindex )
    {
        FormatIdxUsed[dateindex]=1;
        /*fprintf(stderr,"Date idx %d is set to be dirty\n",dateindex); */
    }
}

/*
 * format index between 0x0E and 0x16 also between 0x2D and ox2F denotes
 * date in case when they are built-in Excel97 formats.
 * Nevertheless, those indexes can be used for explicitly stored formats,
 * which are not dates in general.
 * SetFormatIdxUsed marks this formats as already used
 * and excludes them from list of built-in formats
 * preventing misformatting of corresponding data.
 * IsFormatIdxUsed tests this case.
 */
char IsFormatIdxUsed( int format_code )
{
    int dateindex;
    dateindex=BuiltInDateFormatIdx( format_code );
    if ( dateindex )
    {
        /* 	  fprintf(stderr,"Date idx %d is dirty\n",dateindex); */
        return FormatIdxUsed[dateindex]==1;
    }
    else return 0;
}


/* Checks if format denoted by given code is date
 * Format code is index into format table (which is list of XF records
 * in the file
 * Second word of XF record is format type inex
 * format index between 0x0E and 0x16 also between 0x2D and ox2F denotes
 * date.
 * If so, it returns strftime format for this date. Otherwise returns
 * NULL
 */


char *isDateFormat( int format_code )
{
    int index;
    int dateindex;
    if ( format_code>=( int )formatTableIndex )
    {
        CLog(debug) << "Format code " << format_code << " is used before definition";
        return NULL;
    }

    index = formatTable[format_code];
    if ( IsFormatIdxUsed( index ) )
    {
        //CLog(debug) << "Format " << index << " is redefined";
        /* this format is something user-defined --- not a standard built-in date*/
        return NULL;
    }
    dateindex=BuiltInDateFormatIdx( index );
    if ( dateindex )
    {
        if ( forced_date_format ) return forced_date_format;
        return GetBuiltInDateFormat( dateindex );
    }
    else
        return NULL;
}



time_t float2date( double d );
/*
 * Extracts floating point value and formats it
 */

char *number2string( double d,short int format_code )
{
    static char buffer [128];
    char *datefmt;
    if (( datefmt=isDateFormat( format_code ) )!=NULL )
    {
        time_t t = float2date( d );
        strftime( buffer, 127,datefmt, gmtime( &t ) );
    }
    else
    {
        sprintf( buffer,number_format,d );
    }
    return buffer;
}

char *format_double( char *rec,int offset,int format_code )
{
    union { char cc[8];
        double d;
    } dconv;
    char *d,*s;
    int i;
# ifdef WORDS_BIGENDIAN
    for ( s=rec+offset+8,d=dconv.cc,i=0;
            i<8;i++ ) *( d++ )=*( --s );
# else
    for ( s=rec+offset,d=dconv.cc,i=0;
            i<8;i++ ) *( d++ )=*( s++ );
# endif
    return number2string( dconv.d,format_code );
}

/*
 * Formats integer value into static buffer
 */
char *format_int( int value,int format_code )
{
    boost::ignore_unused_variable_warning( format_code );
    static char buffer[12];
    sprintf( buffer,"%i",value );
    return buffer;
}
/*
 * Formats RK record
 */
char* format_rk( char *rec,short int format_code )
{
    double value=0.0;
    int i;

    if ( *( rec ) & 0x02 )
    {
        value=( double )( getlong(( unsigned char* )rec,0 )>>2 );
    }
    else
    {
        union { char cc[8];
            double d;
        } dconv;
        char *d,*s;
        for ( i=0;i<8;i++ )
            dconv.cc[i]='\0';
# ifdef WORDS_BIGENDIAN
        for ( s=rec+4,d=dconv.cc,i=0; i<4;i++ )
            *( d++ )=*( --s );
        dconv.cc[0]=dconv.cc[0] & 0xfc;
# else
        for ( s=rec,d=dconv.cc+4,i=0;
                i<4;i++ ) *( d++ )=*( s++ );
        dconv.cc[3]=dconv.cc[3] & 0xfc;
# endif
        value=dconv.d;
    }
    if ( *( rec ) & 0x01 )
        value=value*0.01;
    return number2string( value,format_code );
}

double round2( double x )
{
    return ( x-floor( x ) )>0.5 ? ceil( x ) : floor( x );
}
/*
 * Converts excel date into time_t
 */
time_t float2date( double f )
{
    /* Hacked version. Excell stores date as floating point count of days
     * since 1.1.1900. or 1.1.1904
     * We are substracting value of 1.1.1970 and multiplying
     * by 86400 thus getting seconds from the epoch
     */
    return ( time_t )round2(( f-date_shift )*86400 );
}

/*
 * Parses SST into array of strings
 */
bool parse_sst( char *sstbuf,int bufsize )
{
    int i; /* index into sst */
    unsigned char *curString; /* pointer into unparsed buffer*/
    unsigned char *barrier=( unsigned char * )sstbuf+bufsize; /*pointer to end of buffer*/
    unsigned char **parsedString;/*pointer into parsed array*/

    sstsize = getlong(( unsigned char* )sstbuf+4,0 );
    sst=( unsigned char** )malloc( sstsize*sizeof( char * ) );

    if ( sst == NULL )
        throw std::runtime_error( "MsWord::ExtractXls: not enough memory" );

    memset( sst,0,sstsize*sizeof( char * ) );
    for ( i=0,parsedString=sst,curString=( unsigned char* )sstbuf+8;
            i<sstsize && curString<barrier; i++,parsedString++ )
    {
        //CLog(debug) << "Parse sst";
        /* 		fprintf(stderr,"copying %d string\n",i); */
        bool bEndFlag;
        *parsedString = ( unsigned char* )copy_unicode_string( &curString, bEndFlag );
        if( !bEndFlag )
            return false;
    }
    /* 	fprintf(stderr,"end sst i=%d sstsize=%d\n",i,sstsize); */

    return true;
}
