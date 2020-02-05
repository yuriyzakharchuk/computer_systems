#include "helpers.h"

std::wstring *read_file(const char *filepath)
{
    std::wifstream t(filepath);
    return new std::wstring (std::istreambuf_iterator<wchar_t>(t), std::istreambuf_iterator<wchar_t>());
}
