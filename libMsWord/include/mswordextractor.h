#ifndef MSWORDEXTRACTOR_H
#define MSWORDEXTRACTOR_H

#include <QString>
#include <boost/function.hpp>

namespace MsWord
{
    void Extract( boost::function<void (unsigned short*)> Writer, const QString& strFileName );
    void ExtractXls( boost::function<void ( unsigned short* )> XlsWriter, const QString& strFileName );
    void ExtractPpt( boost::function<void ( unsigned short* )> PptWriter, const QString& strFileName );
}

#endif // MSWORDEXTRACTOR_H
