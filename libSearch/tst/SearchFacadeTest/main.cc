#include <iostream>
#include <QDebug>
#include <QTextCodec>

#include "searchfacade.h"

using namespace std;

bool OnData( QString Data )
{
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    qDebug() << Data;
    return true;
}

void FileMatched( const QString& strFilename )
{
    qDebug() << strFilename;
}

void SearchDone()
{
    qDebug() << "Search done";
}

int main(int argc, char *argv[])
{
    if( argc < 3 )
    {
        std::cout << "Usage: path pattern" << std::endl;
        return 1;
    }

    TextExtractorFactory::Instance().RegisterExtension( ".txt", "Plain Text Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".doc", "Microsoft Word Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".rtf", "Microsoft Word Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".xls", "Microsoft Excel Spreadsheet Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".ppt", "Microsoft PowerPoint Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".pdf", "Portable Document Format Parser" );

    CSearchFacade searcher;
    SearchOptions options = { argv[ 1 ], QStringList( argv[ 2 ] ), QStringList( "*" ) , false, true, 0, 0, true };

    searcher.SigFileMatched().connect( FileMatched );
    searcher.SigSearchDone().connect( SearchDone );
    searcher.Start( options );

    std::string str;
    getline( cin, str );
    return 0;
}
