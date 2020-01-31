#ifndef TEXT_ANALYZER_HEADER
#define TEXT_ANALYZER_HEADER

#pragma once

#include "helpers.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <climits>

class text_analyzer
{
public:
    explicit text_analyzer(std::string*);
    ~text_analyzer();
    void print_all(std::ostream& os, uint32_t columns);
    void print_frequency(std::ostream& os, uint32_t columns);
    void print_entropy(std::ostream& os);
    void print_information(std::ostream& os);
    void compress(compressin_algorithm algorithm);

private:
    std::string *_text {nullptr};
    std::map<char, long double> *_frequency;
    long double _length;
    long double _entropy;
    long double _information;

    void compute_frequency();
    void compute_entropy();
    void compute_information_count();
};

#endif //#ifndef TEXT_ANALYZER_HEADER
