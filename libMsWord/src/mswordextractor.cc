#include "mswordextractor.h"
#include <catdoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdexcept>
#include <xls.h>
#include <ppt.h>

int signature_check = 1;
int forced_charset = 0; /* Flag which disallow rtf parser override charset*/
int wrap_margin = WRAP_MARGIN;
int ( *get_unicode_char )( FILE *f,long *offset,long fileend ) =NULL;

char *input_buffer;

namespace MsWord
{
    void Extract( boost::function<void ( unsigned short* )> Writer, const QString& strFileName )
    {
        FILE *f;
        source_charset = read_charset( source_csname );
        if ( !source_charset )
            throw std::runtime_error( "MsWord::Extract: src charset not found" );

        set_std_func();
        f=fopen( strFileName.toUtf8().constData(),"rb" );
        if ( !f )
            throw std::runtime_error( "MsWord::Extract: file not found" );

        set_writer( Writer );
        analyze_format( f );
        fclose( f );
    }

    void ExtractXls( boost::function<void ( unsigned short* )> XlsWriter, const QString& strFileName )
    {
        FILE *f, *new_file, *ole_file;

        source_charset = read_charset( source_csname );
        if ( !source_charset )
            throw std::runtime_error( "MsWord::ExtractXls: src charset not found" );

        set_std_func();
        f=fopen( strFileName.toUtf8().constData(),"rb" );
        if ( !f )
            throw std::runtime_error( "MsWord::ExtractXls: src charset not found" );

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
            if( new_file != f )
                fclose(f);
            throw std::runtime_error( "ExtractXls: incorrect file format" );
        }
    }

    void ExtractPpt( boost::function<void ( unsigned short* )> PptWriter, const QString& strFileName )
    {
        FILE *f = fopen( strFileName.toUtf8().constData(),"rb"), *new_file, *ole_file;

        if(!f)
            throw std::runtime_error( "MsWord::ExtractPpt: src charset not found" );

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
            throw std::runtime_error( "ExtractPpt: incorrect file format" );
        }
    }
}
