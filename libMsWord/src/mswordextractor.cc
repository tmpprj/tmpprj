#include "mswordextractor.h"
#include <catdoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdexcept>
#include <xls.h>
#include <ppt.h>
#include <log.h>
#include <exceptions.h>
#include <boost/shared_array.hpp>

#ifdef WIN32
#define strcasecmp _stricmp
#endif

int signature_check = 1;
int forced_charset = 0; /* Flag which disallow rtf parser override charset*/
int wrap_margin = WRAP_MARGIN;
int ( *get_unicode_char )( FILE *f,long *offset,long fileend ) =NULL;

char *input_buffer;

namespace MsWord
{
    void Extract( boost::function<bool ( unsigned short* )> Writer, const QString& strFileName )
    {
        FILE *f = NULL;
        source_charset = read_charset( source_csname );
        if ( !source_charset )
            throw std::runtime_error( "MsWord::Extract: src charset not found" );

        set_std_func();

#ifdef WIN32
        boost::shared_array<wchar_t> filename( new wchar_t[strFileName.size()*4+1] );
        size_t stCount = strFileName.toWCharArray( filename.get() );
        filename[stCount] = 0;
        if( stCount > 0 )
            f = _wfopen( filename.get(), L"rb");
#else
        f = fopen( strFileName.toUtf8().constData(),"rb");
#endif
        if ( !f )
            throw CUserLevelError();

        set_writer( Writer );
        analyze_format( f );
        fclose( f );
    }

    void ExtractXls( boost::function<bool ( unsigned short* )> XlsWriter, const QString& strFileName )
    {
        FILE *f = NULL, *new_file, *ole_file;

        source_charset = read_charset( source_csname );
        if ( !source_charset )
            throw std::runtime_error( "MsWord::ExtractXls: src charset not found" );

        set_std_func();
#ifdef WIN32
        boost::shared_array<wchar_t> filename( new wchar_t[strFileName.size()*4+1] );
        size_t stCount = strFileName.toWCharArray( filename.get() );
        filename[stCount] = 0;
        if( stCount > 0 )
            f = _wfopen( filename.get(), L"rb");
#else
        f = fopen( strFileName.toUtf8().constData(),"rb");
#endif
        if ( !f )
            throw CUserLevelError();

        set_xls_writer( XlsWriter );
        if( ( new_file = ole_init( f, NULL, 0 ) ) != NULL )
        {
            set_ole_func();
            while( ( ole_file = ole_readdir( new_file ) ) != NULL )
            {
                int res=ole_open( ole_file );
                if( res >= 0 )
                {
                    if( strcasecmp( ( (oleEntry*)ole_file )->name , "Workbook" ) == 0
                        || strcasecmp( ( (oleEntry*)ole_file )->name,"Book" ) == 0 )
                    {
                        do_table( ole_file );
                    }
                }
                ole_close(ole_file);
            }
            set_std_func();
            ole_finish();
            fclose(new_file);
        }
        else
        {
            CleanUp();
            if( new_file != f )
                fclose(f);
            throw CUserLevelError( "ExtractXls: incorrect file format" );
        }
        CleanUp();
    }

    void ExtractPpt( boost::function<bool ( unsigned short* )> PptWriter, const QString& strFileName )
    {
        FILE *f = NULL, *new_file, *ole_file;

#ifdef WIN32
        boost::shared_array<wchar_t> filename( new wchar_t[strFileName.size()*4+1] );
        size_t stCount = strFileName.toWCharArray( filename.get() );
        filename[stCount] = 0;
        if( stCount > 0 )
            f = _wfopen( filename.get(), L"rb");
#else
        f = fopen( strFileName.toUtf8().constData(),"rb");
#endif

        if(!f)
            throw CUserLevelError();

        set_ppt_writer( PptWriter );
        if( ( new_file=ole_init( f, NULL, 0 ) ) != NULL )
        {
            set_ole_func();
            while( ( ole_file = ole_readdir( new_file ) ) != NULL )
            {
                int res=ole_open( ole_file );
                if( res >= 0 )
                {
                    if( strcasecmp( ((oleEntry*)ole_file)->name , "PowerPoint Document" ) == 0 )
                        do_ppt( ole_file );
                }
                ole_close(ole_file);
            }
            set_std_func();
            ole_finish();
            fclose(new_file);
        } else
        {
            if( new_file != f )
                fclose(f);
            throw CUserLevelError( "ExtractPpt: incorrect file format" );
        }
    }
}
