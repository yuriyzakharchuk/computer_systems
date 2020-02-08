#ifndef BASE64_HEADER
#define BASE64_HEADER

#include <fstream>
#include <iostream>
#include <cassert>

char *read_file(const char*, size_t *);
unsigned char *base64_encode(const char*, size_t);

#endif