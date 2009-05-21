#include "pdfextractor.h"
#include "GString.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Stream.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "Catalog.h"
#include "Page.h"
#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "CharTypes.h"
#include "UnicodeMap.h"
#include "Error.h"

namespace Pdf
{
    void outputToNull(void *stream, char *text, int len)
    {
        boost::ignore_unused_variable_warning( stream );
        boost::ignore_unused_variable_warning( text );
        boost::ignore_unused_variable_warning( len );
    }

    void Extract( boost::function<void (unsigned int*, size_t)> Writer, const std::string& strFileName )
    {
        std::auto_ptr<PDFDoc> pDoc;
        std::auto_ptr<GString> fileName( new GString( strFileName.c_str() ) );
        std::auto_ptr<TextOutputDev> textOut;
        UnicodeMap* uMap;
        Object info;

        // read config file
        if( NULL == globalParams.get() )
            globalParams = std::auto_ptr<GlobalParams>( new GlobalParams("/libpdf/config") );

        // get mapping to output encoding
        if( !(uMap = globalParams->getTextEncoding()) )
            throw std::runtime_error( "PdfExtractor: unable to read file: " + strFileName );
//        {
//            error(-1, "Couldn't get text encoding");
//            delete fileName;
//            goto err1;
//        }

        pDoc = std::auto_ptr<PDFDoc>( new PDFDoc(fileName.get(), NULL, NULL) );
        if (!pDoc->isOk())
            throw std::runtime_error( "PdfExtractor: unable to read file: " + strFileName );
//        {
//            exitCode = 1;
//            goto err2;
//        }

        int firstPage = 1;
        int lastPage = pDoc->getNumPages();

        GBool physLayout = gFalse;
        GBool rawOrder = gFalse;

        void* NullStream = (void*)0x1;
        textOut = std::auto_ptr<TextOutputDev>( new TextOutputDev( outputToNull, NullStream, physLayout, rawOrder, Writer ) );
        if (textOut->isOk())
        {
            pDoc->displayPages(textOut.get(), firstPage, lastPage, 72, 72, 0, gFalse, gTrue, gFalse);
        }
        uMap->decRefCnt();
    }
}
