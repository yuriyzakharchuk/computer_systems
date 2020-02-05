#include "text_analyzer.h"


text_analyzer::text_analyzer(std::wstring* text)
    : _text(text),
      _frequency (nullptr),
      _length(text->length()),
      _entropy(0)
{
    this->compute_frequency();
    this->compute_entropy();
    this->compute_information_count();
}



text_analyzer::~text_analyzer()
{
    delete _frequency;
    delete _text;
}



void text_analyzer::compute_frequency()
{
    this->_frequency = new std::map<wchar_t, long double>();
    for(const auto& x : *this->_text)
    {
        auto iterator = this->_frequency->find(x);
        if(iterator == this->_frequency->end())
        {
            this->_frequency->insert({x, 1});
        }
        else
        {
            ++iterator->second;
        }
    }
    for(auto& pair : *_frequency)
    {
        pair.second /= static_cast<long double>(_length);
    }
}



void text_analyzer::compute_entropy()
{
    for(const auto& pair : *_frequency)
    {
        _entropy += pair.second * std::log2(1 / pair.second);
    }
}

void text_analyzer::compute_information_count()
{
    _information = _entropy * _length;
}



void text_analyzer::print_frequency(std::basic_ostream<wchar_t> &os, uint32_t columns) const
{
    os << "Probability: \n";
    int flag = 0;
    for (const auto &pair : *_frequency)
    {
        os << pair.first << ": " << pair.second << (((++flag % columns) != 0)? '\t' : '\n');
    }
    os << std::endl;  
}



void text_analyzer::print_entropy(std::basic_ostream<wchar_t> &os) const
{
    os << "Entropy: " << _entropy << '\n';
}



void text_analyzer::print_information(std::basic_ostream<wchar_t> &os) const
{
    os << "Information (bits): " << _information << '\n'
       << "Real bit counter: " << _length * CHAR_BIT << '\n';
}



void text_analyzer::print_all(std::basic_ostream<wchar_t> &os, uint32_t columns) const
{
    this->print_entropy(os);
    this->print_information(os);
    this->print_frequency(os, columns);
}