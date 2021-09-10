#include "InputParser.h"

InputParser::InputParser()
    : it {buffer.begin()} {}

void InputParser::set_buffer(const std::string buffer)
{
    this->buffer = buffer;
}

const std::string InputParser::get_buffer() const
{
    return this->buffer;
}

void InputParser::set_it(std::string::iterator current_iterator)
{
    this->it = current_iterator;
}

const std::string::iterator InputParser::get_it() const
{
    return it;
}

const double InputParser::parse_numbers()
{
    std::string numbers;
    auto it {this->get_it()}; 
    while(it != buffer.end())
    {
        if(*it >= '0' && *it <= '9')
        {
            numbers += *it;
        }
        else if(*it == '.')
        {
            numbers += *it;
        }
        else if(*it == ',')
        {
            numbers += '.';
        }
        else
            break;
        it++;
    }
    this->set_it(it);
    return std::stod(numbers);
}

const char InputParser::parse_variables()
{
    char variable {' '};
    auto it {this->get_it()}; 

    while(it != buffer.end())
    {
        if(*it >= 'A' && *it <= 'Z')
        {
            variable = *it;
            break;
        }
        else if(*it >= 'a' && *it <= 'z')
        {
            variable = *it;
            break;
        }
        else
            break;
        it++;
    }
    
    return variable;
}