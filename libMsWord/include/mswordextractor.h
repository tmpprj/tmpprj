#ifndef MSWORDEXTRACTOR_H
#define MSWORDEXTRACTOR_H

#include <QString>
#include <boost/function.hpp>

namespace MsWord
{
    void Extract( boost::function<bool (unsigned short*)> Writer, const QString& strFileName );
    void ExtractXls( boost::function<bool ( unsigned short* )> XlsWriter, const QString& strFileName );
    void ExtractPpt( boost::function<bool ( unsigned short* )> PptWriter, const QString& strFileName );
}

#endif // MSWORDEXTRACTOR_H
