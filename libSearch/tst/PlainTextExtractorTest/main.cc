#include <iostream>
#include "plaintextextractor.h"
#include <QDebug>

void OnData( const CPlainTextExtractor::structFileData& Data )
{
    qDebug() << "file: " << Data.strFileName << " data: " << Data.strFileData;
}

int main(int argc, char *argv[])
{
    if( argc != 2 )
    {
        std::cout << "Usage: test file" << std::endl;
        return 1;
    }

    CPlainTextExtractor TextExt;

    TextExt.SigDataObtained().connect( OnData );
    TextExt.OnData( argv[1] );

    std::string s;
    std::cin >> s;

    TextExt.OnStop();

    return 0;
}
