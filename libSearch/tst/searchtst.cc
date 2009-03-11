#include <boost/signal.hpp>
#include <QtCore>
#include <string>
#include <iostream>
#include "searchfacade.h"

using namespace std;

void FileProcessed( const std::string& strFileName, const QString& strFileData )
{
    std::cout << "FILE: " << strFileName << " DATA: " << strFileData.toStdString() << endl;
}

void FileFound( const std::string& strFilename )
{
    qDebug() << "FOUND: " << strFilename.c_str() << endl;
}

int main( int argc, char* argv[] )
{
    if( argc != 3 )
    {
        cout << "Usage: test path mask" << endl;
        return 1;
    }

    CSearchFacade search;
    Masks_t masks;
    masks.push_back( argv[ 2 ] );
    search.SigFileProcessed().connect( FileProcessed );
    search.SigFileFound().connect( FileFound );

    search.Start( argv[ 1 ], masks );

    string str;
    getline( cin, str );
    
    return 0;
}

