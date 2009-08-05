#include <iostream>
#include <QDebug>
#include <unistd.h>
#include <QTextCodec>

#include "filesearcher.h"

using namespace std;

void FileFound( const QString& strFilename )
{
}

int main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        std::cout << "Usage: path" << std::endl;
        return 1;
    }

    qDebug() << QString( argv[1] );
    CFileSearcher searcher;
    searcher.SigFileFound().connect( FileFound );
    searcher.StartSearch( QString( argv[ 1 ] ), QStringList( "*" ), true, 0, 100000000 );

    return 0;
}
