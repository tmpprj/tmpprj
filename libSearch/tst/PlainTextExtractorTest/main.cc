#include <iostream>
#include "plaintextextractor.h"

void OnData( const std::string& strFileName, const QString& strData )
{
    std::cout << "file: " << strFileName << " data: " << strData.toStdString() << std::endl;
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
    TextExt.OnNewFile( argv[1] );

    std::string s;
    std::cin >> s;

    TextExt.OnStop();

    return 0;
}
