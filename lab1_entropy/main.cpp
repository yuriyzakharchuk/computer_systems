#include <map>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

std::map<char, int>* compute_freq(const std::string&);
void print_result(const std::map<char, int>*);

int main(int argc, char** argv)
{
    switch(getopt(argc, argv, "u:f:r:"))
    {
        case 'f':
            auto char_map = compute_freq("111222333");
            for(auto pair : *char_map)
            {
                std::cout << pair.first << ": " << pair.second << std::endl;
            }
            delete char_map;
            break;
        case 'u':
            std::cout << optarg << std::endl;
            break;
        case 'r':
            std::cout << optarg << std::endl;
            break;
        default:
            std::cout << "usage: an [-f|-u] [path|url]" << std::endl;
            std::exit(EXIT_FAILURE);
    }
}


std::map<char, int>* compute_freq(const std::string& text)
{
    auto char_map = new std::map<char, int>();
    for(auto x : text)
    {
        auto iter = char_map->find(x);
        if(iter != char_map->end())
        {
            char_map->insert(std::pair<char, int>(x, 1));
        }
        else
        {
            ++(iter->second);
        }
    }
    return char_map;
}



