#ifndef CTXTTEXTEXTRACTOR_H
#define CTXTTEXTEXTRACTOR_H

#include "plaintextextractor.h"
#include <string>
#include <fstream>
#include "charsetdetector.h"
#include <QTextCodec>
#include "log.hpp"

class CTxtTextExtractor: public ITextExtractor
{
public:

    CTxtTextExtractor();

    virtual void Extract( const std::string strFileName, QString& strText )
    {
        std::string strLine;
        std::ifstream file( strFileName.c_str(), std::ifstream::in );

        CCharsetDetector CharDet;
        std::string strContent;
        while( file.good() )
        {
            getline( file, strLine );

            if( strLine.empty() )
                break;

            if( !CharDet.Done() )
                CharDet.HandleData( strLine.data(), strLine.size() );

            strContent += strLine + '\n';
        }

        CLog log;
        log << strContent << std::endl;

        CharDet.DataEnd();

        std::string strCharset = CharDet.GetCharset();

        QTextCodec* pTextCodec = strCharset.empty() ? QTextCodec::codecForLocale() : QTextCodec::codecForName( strCharset.c_str() );
        if( NULL == pTextCodec )
            strText.fromStdString( strContent );
        else
            strText = pTextCodec->toUnicode( strContent.c_str() );
    }

private:


};

#endif // CTXTTEXTEXTRACTOR_H
