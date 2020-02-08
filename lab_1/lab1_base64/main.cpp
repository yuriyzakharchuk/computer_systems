#include "base64.h"

int main(int argc, char **argv)
{
    try
    {
        if(argc != 2)
        {
            std::cout << "usage: encode path" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        size_t buffer_len;
        auto file = read_file(argv[1], &buffer_len);
        auto encoded = base64_encode(file, buffer_len);
        std::cout << "Base64 encoded: " << encoded << std::endl;
        delete[] file;
        delete[] encoded;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


