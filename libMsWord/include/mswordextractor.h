#ifndef MSWORDEXTRACTOR_H
#define MSWORDEXTRACTOR_H

#include <string>

typedef void (*WriterFunc)(unsigned short int* );

void Extract( WriterFunc Writer, const std::string& strFileName );

#endif // MSWORDEXTRACTOR_H
