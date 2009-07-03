#include "mswordextractor.h"
#include <iostream>
#include <iomanip>

bool WriterF( unsigned short int* pBuf )
{
    std::cout << "WriterFunc:" << std::endl;
    while( *pBuf )
    {
        std::cout << std::hex << std::setw(4) << std::setfill('0') << *pBuf << " ";
        pBuf++;
    }
    return true;
}

int main(int argc, char **argv)
{
    if( argc < 2 )
        return 1;
    MsWord::ExtractPpt( WriterF, argv[1] );

    return 0;
}
