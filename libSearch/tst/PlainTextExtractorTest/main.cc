#include <iostream>
#include "plaintextextractor.h"
#include <QDebug>
#include <unistd.h>
#include <QTextCodec>


bool OnData( QString Data )
{
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    qDebug() << Data;
    return true;
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

    ITextExtractor* pExtractor = TextExtractorFactory::Instance().GetExtractor( argv[1] );
    pExtractor->SigChunk().connect( OnData );

    pExtractor->Extract( argv[1], 10000 );
    return 0;
}
