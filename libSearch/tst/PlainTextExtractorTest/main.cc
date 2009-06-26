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

    TextExtractorFactory::Instance().RegisterExtension( ".txt", "TXT Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".doc", "DOC Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".rtf", "DOC Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".xls", "XLS Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".ppt", "PPT Parser" );
    TextExtractorFactory::Instance().RegisterExtension( ".pdf", "PDF Parser" );

    CPlainTextExtractor TextExt;

    TextExt.SigDataObtained().connect( OnData );
    TextExt.OnData( argv[1] );

    
    std::string str;
    std::getline(std::cin, str);

    TextExt.OnStop();

    return 0;
}
