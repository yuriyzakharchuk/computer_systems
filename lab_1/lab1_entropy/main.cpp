#include "helpers.h"
#include "text_analyzer.h"
#include <assert.h>

int main(int argc, char **argv)
{
    std::locale::global(std::locale("en_US.utf8"));
    std::wcout.setf(std::ios::fixed);
    if(argc != 2)
    {
        std::cout << "usage: an -f|-r] [path|raw text]" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    text_analyzer(read_file(argv[1])).print_all(std::wcout, 4);
}
