#ifndef AH_HEADER
#define AH_HEADER

#pragma once

#include <string>

std::string* read_file(std::string path);
std::string* download_file(std::string url);

enum class compressin_algorithm
{
    zip,
    rar,
    gzip,
    bzip2,
    xz
};

#endif //#ifndef AH_HEADER