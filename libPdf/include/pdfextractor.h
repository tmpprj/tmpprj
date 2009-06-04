#ifndef PDFEXTRACTOR_H
#define PDFEXTRACTOR_H
#include <boost/function.hpp>
#include <QString>

namespace Pdf
{
    void Extract( boost::function<void (unsigned int*, size_t)> Writer, const QString& strFileName );
}
#endif // PDFEXTRACTOR_H
