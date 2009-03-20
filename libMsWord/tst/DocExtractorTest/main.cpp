//#include <QtCore/QCoreApplication>
#include "mswordextractor.h"
#include <iostream>

void WriterF( unsigned short int* pBuf )
{
    std::cout << "WriterFunc:" << std::endl;
    while( *pBuf )
    {
        std::cout << std::hex << *pBuf << " ";
        pBuf++;
    }
}

int main(int argc, char **argv)
{
    if( argc < 2 )
        return 1;
    MsWord::Extract( WriterF, argv[1] );

    return 0;
//    QCoreApplication a(argc, argv);

//    return a.exec();

}
