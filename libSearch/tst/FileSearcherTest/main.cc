#include <iostream>
#include <QDebug>
#include <unistd.h>
#include <QTextCodec>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "filesearcher.h"

using namespace std;

size_t stFilesCount = 0;

void FileFound( const QString& strFilename )
{
    ++stFilesCount;
}

void Done()
{
    qDebug() << "Done, files count = " << stFilesCount;
    ::exit(0);
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
    searcher.SigDone().connect( Done );
    searcher.StartSearch( QString( argv[ 1 ] ), QStringList( "*" ), true, 0, 100000000L );

    boost::this_thread::sleep( boost::posix_time::second_clock::local_time() + boost::posix_time::seconds(1000000) );

    return 0;
}
