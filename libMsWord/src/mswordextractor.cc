#include "mswordextractor.h"
#include <catdoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdexcept>
//#include <log.hpp>

int signature_check = 1;
int forced_charset = 0; /* Flag which disallow rtf parser override charset*/
int wrap_margin = WRAP_MARGIN;
int (*get_unicode_char)(FILE *f,long *offset,long fileend) =NULL;

char *input_buffer;

namespace MsWord
{
    void Extract( boost::function<void (unsigned short*)> Writer, const std::string& strFileName )
    {
        FILE *f;
        int c;
        short int *tmp_charset;
        input_buffer=(char*)malloc(FILE_BUFFER);
        if (!input_buffer)
            throw std::runtime_error( "MsWord::Extract: memory allocating error" );

        source_charset = read_charset(source_csname);
        if (!source_charset)
            throw std::runtime_error( "MsWord::Extract: src charset not found" );

        set_std_func();
        c=0;
        f=fopen(strFileName.c_str(),"rb");
        if (!f)
        {
            c=1;
            perror("catdoc");
            exit(0);
        }
        if (input_buffer) {
            if (setvbuf(f,input_buffer,_IOFBF,FILE_BUFFER)) {
                //perror();
            }
        }
        set_writer( Writer );
        c=analyze_format(f);
        fclose(f);
    }

}
