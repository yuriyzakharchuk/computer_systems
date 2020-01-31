#ifndef AH_HEADER
#define AH_HEADER

#pragma once

#include <string>
#include <fstream>


std::string* read_file(const char *text);

enum class compressin_algorithm
{
    zip,
    rar,
    gzip,
    bzip2,
    xz
};

#endif //#ifndef AH_HEADER