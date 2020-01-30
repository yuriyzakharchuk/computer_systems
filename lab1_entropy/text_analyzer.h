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

class text_analyzer
{
private:
    double _text_length;
    std::string *_text {nullptr};
    std::map<char, uint64_t> *_frequency {nullptr};
    void compute_frequency();
    void compute_entropy();
    void compute_all();

public:
    explicit text_analyzer(std::string*);
    ~text_analyzer();
    void print_entropy(std::ostream& os);
    void print_probability(std::ostream& os);
    void print_brief(std::ostream& os);
    void print_all(std::ostream& os);
    void compress(compressin_algorithm algorithm);
};

#endif //#ifndef TEXT_ANALYZER_HEADER
