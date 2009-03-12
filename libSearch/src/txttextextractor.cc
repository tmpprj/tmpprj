#include "txttextextractor.h"

CTxtTextExtractor::CTxtTextExtractor()
{
}

void CTxtTextExtractor::Extract( const std::string strFileName, QString& strText )
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

    CLog() << "Content: " << strContent << std::endl;

    CharDet.DataEnd();

    std::string strCharset = CharDet.GetCharset();

    CLog() << "Detected charset: " << strCharset << std::endl;

    QTextCodec* pTextCodec = strCharset.empty() ? QTextCodec::codecForLocale() : QTextCodec::codecForName( strCharset.c_str() );
    if( NULL == pTextCodec )
    {
        CLog() << "Cant get codec" << std::endl;
        strText.fromStdString( strContent );
    }
    else
        strText = pTextCodec->toUnicode( strContent.data() );
}

//namespace
//{
//    ITextExtractor* CreateTxt()
//    {
//        return new CTxtTextExtractor;
//    }
//
//    const bool bTxtReged = TextExtractorFactory::Instance().RegisterExtractor( ".txt", CreateTxt() );
//}
