#include <boost/signal.hpp>
#include <glob.h>
#include <string>
#include <iostream>
#include "searchfacade.h"

using namespace std;

void FileProcessed( std::string strFilename )
{
    cout << strFilename << endl;
}

int main( int argc, char* argv[] )
{
    if( argc != 3 )
    {
        cout << "Usage: test path mask" << endl;
        return 1;
    }

    SearchFacade search;
    Masks_t masks;
    masks.push_back( argv[ 2 ] );
    search.SigFileProcessed().connect( FileProcessed );
    
    search.StartSearch( argv[ 1 ], masks );

    cout << "Stopped" << endl;
    string str;
    getline( cin, str );
    search.Stop();
    
    return 0;
}

