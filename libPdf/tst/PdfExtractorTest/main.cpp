#include <QtCore/QCoreApplication>
#include <pdfextractor.h>
#include <iostream>

bool WriterF( unsigned int* pBuf, size_t stLen )
{
    std::cout << "WriterFunc: len=" << stLen << std::endl;
    for( size_t i = 0; i < stLen; ++i )
    {
        std::cout << std::hex << pBuf[i] << " ";
    }
    std::cout << std::endl;
    return true;
}

int main(int argc, char **argv)
{
    if( argc < 2 )
        return 1;

    Pdf::Extract( WriterF, argv[1] );

    return 0;
}
