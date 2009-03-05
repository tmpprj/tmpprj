#include "ctxttextextractor.h"

CTxtTextExtractor::CTxtTextExtractor()
{
}

namespace
{
    ITextExtractor* CreateTxt()
    {
        return new CTxtTextExtractor;
    }

    const bool bTxtReged = TextExtractorFactory::Instance().RegisterExtractor( ".txt", CreateTxt() );
}
