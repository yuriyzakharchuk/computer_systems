#include "text_analyzer.h"


text_analyzer::text_analyzer(std::string* text)
    : _text(text)//, _text_length(static_cast<double>(text->length))
{

}

text_analyzer::~text_analyzer()
{
    delete _frequency;
}

void text_analyzer::compute_all()
{

}

void text_analyzer::compute_entropy()
{

}

void text_analyzer::compute_frequency()
{

    this->_frequency = new std::map<char, uint64_t>();
    for(auto x : *this->_text)
    {
        auto iter = this->_frequency->find(x);
        if(iter == this->_frequency->end())
        {
            this->_frequency->insert(std::pair<char, uint64_t>(x, 1));
        }
        else
        {
            ++iter->second;
        }
    }
}

void text_analyzer::print_probability(std::ostream& os)
{
    if(_frequency)
    {
        os << "Probability: \n";
        for(auto& pair : *_frequency)
        {
            os << pair.first << ": " << pair.second / _text_length << '\n';
        }
    }
    else
    {
        compute_frequency();
        print_probability(os);
    }    
}