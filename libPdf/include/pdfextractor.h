#ifndef PDFEXTRACTOR_H
#define PDFEXTRACTOR_H
#include <string>
#include <boost/function.hpp>

namespace Pdf
{
    void Extract( boost::function<void (unsigned int*, size_t)> Writer, const std::string& strFileName );
}
#endif // PDFEXTRACTOR_H
