#ifndef TEXT_ANALYZER_HEADER
#define TEXT_ANALYZER_HEADER

#pragma once

#include "helpers.h"
#include <string>
#include <map>
#include <iostream>
#include <cmath>
#include <climits>

class text_analyzer
{
public:
    explicit text_analyzer (std::wstring*);
    ~text_analyzer ();
    text_analyzer(const text_analyzer&) = delete;
    text_analyzer& operator=(const text_analyzer&) = delete;
    
    void print_all(std::basic_ostream<wchar_t>& os, uint32_t columns) const;
    void print_frequency(std::basic_ostream<wchar_t>& os, uint32_t columns) const;
    void print_entropy(std::basic_ostream<wchar_t>& os) const;
    void print_information(std::basic_ostream<wchar_t>& os) const;

private:
    std::wstring *_text;
    std::map<wchar_t, long double> *_frequency;
    size_t _length;
    long double _entropy;
    long double _information;

    void compute_frequency();
    void compute_entropy();
    void compute_information_count();
};

#endif // TEXT_ANALYZER_HEADER
