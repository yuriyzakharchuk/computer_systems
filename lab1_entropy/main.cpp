#include "helpers.h"
#include "text_analyzer.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    std::cout.setf(std::ios::fixed);
    switch(static_cast<char>(getopt(argc, argv, "f:r:")))
    {
        case 'f':
        {
            auto a = read_file(optarg);
            for(auto& x : *a)
            {
                std::cout << x << std::endl;
            }
            text_analyzer analyzer(a);
            analyzer.print_all(std::cout, 4);
            break;
        }
        case 'r':
        {
            std::string a(optarg);
            for(auto const &x : a)
            {
                std::cout << x << std::endl;
            }
            text_analyzer analyzer(&a);
            analyzer.print_all(std::cout, 4);
            break;
        }
        default:
        {
            std::cout << "usage: an [-f|-r] [path|raw text]" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}