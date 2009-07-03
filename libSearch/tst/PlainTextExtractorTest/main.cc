#include <iostream>
#include "plaintextextractor.h"
#include <QDebug>
#include <unistd.h>
#include <QTextCodec>


void OnData( const CPlainTextExtractor::structFileData& Data )
{
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("CP1251") );
    qDebug() << "file: " << Data.strFileName << " data: " << Data.strFileData;
}

int main(int argc, char *argv[])
{
    if( argc != 2 )
    {
        std::cout << "Usage: test file" << std::endl;
        return 1;
    }

    TextExtractorFactory::Instance().RegisterExtension( ".txt", "Plain Text Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".doc", "Microsoft Word Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".rtf", "Microsoft Word Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".xls", "Microsoft Excel Spreadsheet Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".ppt", "Microsoft PowerPoint Document Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".pdf", "Portable Document Format Parser" );

    CPlainTextExtractor TextExt;

    TextExt.SigDataObtained().connect( OnData );
    TextExt.OnData( argv[1] );
//
//
//    std::string str;
//    std::getline(std::cin, str);
//
//    TextExt.OnStop();

    return 0;
}
