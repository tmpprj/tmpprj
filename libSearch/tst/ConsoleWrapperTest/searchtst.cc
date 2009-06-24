#include <boost/signal.hpp>
#include <QtCore>
#include <QFile>
#include <string>
#include <iostream>
#include <fstream>
#include "searchfacade.h"

using namespace std;

void DataObtained( const CPlainTextExtractor::structFileData&  )
{
//    qDebug() << "FILE: " << strFileName.c_str() << " DATA: " << strFileData << endl;
}

void FileFound( const QString& strFilename )
{
    qDebug() << "FOUND: " << strFilename << endl;
}

void FileMatched( const CPatternMatcher::structFindData& Data )
{
    qDebug() << "MATCHED: " << Data.strFileName << '\t' << Data.bFound << endl;
}

void GetPatterns( PatternsContainer& patterns )
{
    QTextCodec* pTextCodec = QTextCodec::codecForLocale();
    if( NULL == pTextCodec )
        return;

    ifstream file( "patterns.txt" );
    if( !file.is_open() )
        return;

    while( !file.eof() )
    {
        std::string str;
        getline( file, str );

        QString strText = pTextCodec->toUnicode( QByteArray( str.c_str(), str.size() ) );

        if( !strText.isEmpty() )
            patterns.push_back( std::string( ( const char* )strText.utf16(), strText.size() * 2 ) );
    }

    qDebug() << "Patterns count: " << patterns.size();
}

int main( int argc, char* argv[] )
{
    if( argc != 3 )
    {
        cout << "Usage: test path mask" << endl;
        return 1;
    }


    CSearchFacade search;

    PatternsContainer patterns;
    GetPatterns( patterns );

    Masks_t masks;
    masks.push_back( argv[ 2 ] );
    search.SigDataObtained().connect( DataObtained );
    search.SigFileFound().connect( FileFound );
    search.SigFileMatched().connect( FileMatched );

    search.Start( argv[ 1 ], patterns, masks );

    string str;
    getline( cin, str );
    qDebug() << "Done" << endl;

    return 0;
}

