//#include <catdoc.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <ctype.h>
//#include <iostream>
//
//int signature_check = 1;
//int forced_charset = 0; /* Flag which disallow rtf parser override charset*/
//int wrap_margin = WRAP_MARGIN;
////int (*get_unicode_char)(FILE *f,long *offset,long fileend) =NULL;
//
//char *input_buffer, *output_buffer;
//
//void WriterF( unsigned short int* pBuf )
//{
//    std::cout << "WriterFunc:" << std::endl;
//    while( *pBuf++ )
//    {
//        std::cout << (int)*pBuf << " ";
//    }
//}
//
//int main(int argc, char **argv) {
//        FILE *f;
//        int c,i;
//        char *tempname;
//        short int *tmp_charset;
//        int stdin_processed=0;
//        input_buffer=(char*)malloc(FILE_BUFFER);
//        if (!input_buffer) {
//                fprintf(stderr,"Input buffer not allocated\n");
//        }
//        source_charset = read_charset(source_csname);
//        if (!source_charset) exit(1);
//        if (strncmp(dest_csname,"utf-8",6)) {
//                tmp_charset = read_charset(dest_csname);
//                if (!tmp_charset) exit(1);
//                target_charset= make_reverse_map(tmp_charset);
//                free(tmp_charset);
//        } else {
//                target_charset = NULL;
//        }
//
//        set_std_func();
//        c=0;
//        f=fopen(argv[1],"rb");
//        if (!f)
//        {
//                c=1;
//                perror("catdoc");
//                exit(0);
//        }
//        if (input_buffer) {
//                if (setvbuf(f,input_buffer,_IOFBF,FILE_BUFFER)) {
//                        perror(argv[1]);
//                }
//        }
//        set_writer( WriterF );
//        c=analyze_format(f);
//        fclose(f);
//        return c;
////    QCoreApplication a(argc, argv);
//
////    return a.exec();
//
//}
///************************************************************************/
///* Displays  help message                                               */
///************************************************************************/
//void help (void) {
//        printf("Usage:\n catdoc [-vu8btawxlV] [-m number] [-s charset] "
//                        "[-d charset] [ -f format] files\n");
//}
//
