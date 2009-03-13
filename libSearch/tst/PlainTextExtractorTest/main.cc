#include <iostream>
#include "plaintextextractor.h"
#include <QDebug>

void OnData( const std::string& strFileName, const QString& strData )
{
    qDebug() << "file: " << QString::fromStdString(strFileName) << " data: " << strData;
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
