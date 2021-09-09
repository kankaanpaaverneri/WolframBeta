#include "InputParser.h"

InputParser::InputParser()
    : position {0} {}

void InputParser::set_buffer(const std::string buffer)
{
    this->buffer = buffer;
}

const std::string InputParser::get_buffer() const
{
    return this->buffer;
}

double InputParser::parse_numbers()
{
    std::string numbers;
    for(const char ch: buffer)
    {
        if(ch >= '0' || ch <= '9')
        {
            numbers += ch;
        }
        else if(ch == '.' || ch == ',')
        {
            numbers += '.';
        }
    }
    return std::stod(numbers);
}