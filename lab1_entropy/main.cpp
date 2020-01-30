#include "helpers.h"
#include "text_analyzer.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    switch(static_cast<char>(getopt(argc, argv, "u:f:r:")))
    {
        case 'f':
        {
            text_analyzer analyzer(read_file(optarg));
            analyzer.print_probability(std::cout);
            break;
        }
        case 'u':
        {
            text_analyzer analyzer(download_file(optarg));
            analyzer.print_probability(std::cout);
            break;
        }
        case 'r':
        {
            text_analyzer analyzer(new std::string(optarg));
            analyzer.print_probability(std::cout);
            break;
        }
        default:
        {
            std::cout << "usage: an [-f|-u] [path|url]" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}