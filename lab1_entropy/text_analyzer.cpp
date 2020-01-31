#include "text_analyzer.h"



text_analyzer::text_analyzer(std::string* text)
    : _text(text),
      _frequency (nullptr),
      _length(static_cast<long double>(text->length())),
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
    this->_frequency = new std::map<char, long double>();
    for(auto& x : *this->_text)
    {
        auto iter = this->_frequency->find(x);
        if(iter == this->_frequency->end())
        {
            this->_frequency->insert({x, 1});
        }
        else
        {
            ++iter->second;
        }
    }
    for(auto& pair : *_frequency)
    {
        pair.second /= _length;
    }
}



void text_analyzer::compute_entropy()
{
    for(auto& pair : *_frequency)
    {
        _entropy += pair.second * std::log2(1 / pair.second);
    }
}

void text_analyzer::compute_information_count()
{
    _information = _entropy * _length;
}



void text_analyzer::print_frequency(std::ostream& os, uint32_t columns)
{
    os << "Probability: \n";
    int flag = 0;
    for (auto pair = _frequency->begin(); pair != _frequency->end(); ++pair)
    {
        os << pair->first << ": " << pair->second << (((++flag % columns) != 0)? '\t' : '\n');
    }
    os << std::endl;  
}



void text_analyzer::print_entropy(std::ostream& os)
{
    os << "Entropy: " << _entropy << '\n';
}



void text_analyzer::print_information(std::ostream& os)
{
    os << "Information (bits): " << _information << '\n'
       << "Real bit counter: " << _length * CHAR_BIT << '\n';
}



void text_analyzer::print_all(std::ostream& os, uint32_t columns)
{
    this->print_entropy(os);
    this->print_information(os);
    this->print_frequency(os, columns);
}