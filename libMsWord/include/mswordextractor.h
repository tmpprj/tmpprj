#ifndef MSWORDEXTRACTOR_H
#define MSWORDEXTRACTOR_H

#include <string>
#include <boost/function.hpp>

namespace MsWord
{
    void Extract( boost::function<void (unsigned short*)> Writer, const std::string& strFileName );
}

#endif // MSWORDEXTRACTOR_H
