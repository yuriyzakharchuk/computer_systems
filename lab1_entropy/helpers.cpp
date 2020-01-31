#include "helpers.h"

std::string* read_file(const char *filepath)
{
    std::ifstream t(filepath);
    return new std::string ((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
}

