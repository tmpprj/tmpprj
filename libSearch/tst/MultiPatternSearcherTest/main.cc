#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "multipatternsearcher.h"

using namespace std;

void PrintUsage()
{
    cout << "Usage: " << endl;
    cout << "\tMultiPatternSearcherTest <filename>" << endl;
}

string ReadFileData( const char* szFilename )
{
    ifstream file( szFilename );
    if( !file.is_open() )
        throw runtime_error( "Cannot open file" );

    string strRet;
    char buf[ 1024 ];
    while( !file.eof() )
    {
        file.read( buf, sizeof( buf ) );

        strRet += string( buf, file.gcount() );
    }

    return strRet;
}

int main( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        PrintUsage();
        return 1;
    }

    string strData = ReadFileData( argv[ 1 ] );
    cout << "File read ok." << endl;
    cout << "Enter patterns (to finish press Ctrl-D): ";

    PatternsContainer patterns;
    while( !cin.eof() )
    {
        string strPattern;
        cin >> strPattern;
        patterns.push_back( strPattern );
    }

    MultiPatternSearcher searcher;
    searcher.LoadPatterns( patterns );

    PatternMatchContainer match;
    searcher.FindPatterns( strData, match );

    cout << "Patterns found: " << match.size() << endl;

    return 0;
}
