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

bool InputParser::parse_buffer()
{
    auto it {InputParser::get_buffer().begin()};
    while(it != InputParser::get_buffer().end())
    {
        struct monomial m {0, NOT_FOUND, NOT_FOUND};
        if(InputParser::is_number(it))
        {
            if((const unsigned double number = InputParser::parse_numbers()) != 0)
            {
                m.num_or_var.number = number;
            }
        }
        else if(InputParser::is_variable(it))
        {
            if((const char variable = InputParser::parse_variables()) != NOT_FOUND)
            {
                m.num_or_var.variable = variable;
            }
        }
        else if(InputParser::is_power_sign(it))
        {
            if((const char power_sign = InputParser::parse_power_sign()) != NOT_FOUND)
            {
                m.sign = power_sign;
            }
        }
        else if(InputParser::is_multiplication_sign(it))
        {
            if((const char multiplication_sign = InputParser::parse_multiplication_sign()) != NOT_FOUND)
            {
                m.sign = multiplication_sign;
            }
        }
        else if(InputParser::is_division_sign(it))
        {
            if((const char division_sign = InputParser::parse_division_sign()) != NOT_FOUND)
            {
                m.sign = division_sign;
            }
        }
        else if(InputParser::is_minus_sign(it))
        {
            if((const char minus_sign = InputParser::parse_minus_sign()) != NOT_FOUND)
            {
                m.sign = minus_sign;
            }
        }
        else if(InputParser::is_plus_sign(it))
        {
            if((const char plus_sign = InputParser::parse_plus_sign()) != NOT_FOUND)
            {
                m.sign = plus_sign;
            }
        }
        else
        {
            break;
        }
        it++;
    }
    return true;
}

bool InputParser::is_number(std::string::iterator it)
{
    if(*it >= '0' && *it <= '9')
        return true;

    return false;
}

bool InputParser::is_variable(std::string::iterator it)
{
    if((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z'))
        return true;
    
    return false;
}

bool InputParser::is_power_sign(std::string::iterator it)
{
    if(*it == '^')
        return true;
    
    return false;
}

bool InputParser::is_multiplication_sign(std::string::iterator it)
{
    if(*it == '*')
        return true;
    
    return false;
}

bool InputParser::is_division_sign(std::string::iterator it)
{
    if(*it == '/')
        return true;
    
    return false;
}

bool InputParser::is_minus_sign(std::string::iterator it)
{
    if(*it == '-')
        return true;
    
    return false;
}

bool InputParser::is_plus_sign(std::string::iterator it)
{
    if(*it == '+')
        return true;
    
    return false;
}

const double InputParser::parse_numbers()
{
    std::string numbers {'0'};
    auto it {InputParser::get_it()}; 
    while(it != buffer.end())
    {
        if(InputParser::is_number(it))
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
    InputParser::set_it(++it);
    return std::stod(numbers);
}

const char InputParser::parse_variables()
{
    char variable {NOT_FOUND};
    auto it {InputParser::get_it()}; 

    if(it != buffer.end())
    {
        if(InputParser::is_variable(it))
            variable = *it;
    }
    InputParser::set_it(++it);
    return variable;
}

const char InputParser::parse_multiplication_sign()
{
    char multiplication_sign {NOT_FOUND};
    auto it {InputParser::get_it()};
    if(it != buffer.end())
    {
        if(InputParser::is_multiplication_sign(it))
            multiplication_sign = *it;
    }
    InputParser::set_it(++it);
    return multiplication_sign;
}

const char InputParser::parse_plus_sign()
{
    char plus_sign {NOT_FOUND};
    auto it {InputParser::get_it()};

    if(it != buffer.end())
    {
        if(InputParser::is_plus_sign(it))
            plus_sign = *it;
    }
    InputParser::set_it(++it);
    return plus_sign;
}

const char InputParser::parse_minus_sign()
{
    char minus_sign {NOT_FOUND};
    auto it {InputParser::get_it()};

    if(it != buffer.end())
    {
        if(InputParser::is_minus_sign(it))
            minus_sign = *it;
    }
    InputParser::set_it(++it);
    return minus_sign;
}

const char InputParser::parse_division_sign()
{
    char division_sign {NOT_FOUND};
    auto it {InputParser::get_it()};

    if(it != buffer.end())
    {
        if(InputParser::is_division_sign(it))
            division_sign = *it;
    }
    InputParser::set_it(++it);
    return division_sign;
}

const char InputParser::parse_power_sign()
{
    char power_sign {NOT_FOUND};
    auto it {this->get_it()};

    if(it != buffer.end())
    {
        if(InputParser::is_power_sign(it))
            power_sign = *it;
    }
    this->set_it(++it);
    return power_sign;
}
