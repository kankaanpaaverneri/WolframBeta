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

struct value InputParser::init_value(struct value value)
{
    struct value new_value {};
    value = new_value;
    return value;
}

bool InputParser::parse_buffer()
{
    auto it {InputParser::get_buffer().begin()};
    struct value value {NOT_FOUND, NOT_NUMBER};

    while(it != buffer.end())
    {
        if(InputParser::is_number(InputParser::it))
        {
            double number {NOT_NUMBER};
            if((number = InputParser::parse_numbers()) != NOT_NUMBER)
            {
                if(it == InputParser::get_buffer().begin())
                    value.sign = '+';
                value.number_or_variable.number = number;
            }
        }
        else if(InputParser::is_variable(InputParser::it))
        {
            char variable {NOT_FOUND};
            if((variable = InputParser::parse_variables()) != NOT_FOUND)
            {
                value.number_or_variable.variable = variable;
            }
        }
        else if(InputParser::is_power_sign(InputParser::it))
        {
            char power_sign {NOT_FOUND};
            if((power_sign = InputParser::parse_power_sign()) != NOT_FOUND)
            {
                value.special_sign = power_sign;
            }
        }
        else if(InputParser::is_multiplication_sign(InputParser::it))
        {
            char multiplication_sign {NOT_FOUND};
            if((multiplication_sign = InputParser::parse_multiplication_sign()) != NOT_FOUND)
            {
                value.special_sign = multiplication_sign;
            }
        }
        else if(InputParser::is_division_sign(InputParser::it))
        {
            char division_sign {NOT_FOUND};
            if((division_sign = InputParser::parse_division_sign()) != NOT_FOUND)
            {
                value.special_sign = division_sign;
            }
        }
        else if(InputParser::is_minus_sign(InputParser::it))
        {
            char minus_sign {NOT_FOUND};
            if((minus_sign = InputParser::parse_minus_sign()) != NOT_FOUND)
            {
                value.sign = minus_sign;
            }
        }
        else if(InputParser::is_plus_sign(InputParser::it))
        {
            char plus_sign {NOT_FOUND};
            if((plus_sign = InputParser::parse_plus_sign()) != NOT_FOUND)
            {
                value.sign = plus_sign;
            }
        }
        else
            return false;

        if(InputParser::value_is_full(value))
        {
            values.push_back(value);
            value = InputParser::init_value(value);
        }
        
        it = InputParser::get_it();
    }
    return true;
}

bool InputParser::value_is_full(struct value value)
{
    int counter {0};
    if(value.sign != NOT_FOUND)
        counter++;
    
    if(value.number_or_variable.number != NOT_NUMBER)
        counter++;
    
    if(value.number_or_variable.variable != NOT_FOUND)
        counter++;
    
    if(counter > 2)
        return true;
    
    return false;
}

void InputParser::display_values()
{
    for(auto value: values)
    {
        std::cout << "sign: " << value.sign << " ";
        if(value.number_or_variable.variable != NOT_FOUND)
        {
            printf("%c", value.number_or_variable.variable);
        }
        if(value.number_or_variable.number != NOT_NUMBER)
        {
            printf("%.2f", value.number_or_variable.number);
        }
        std::cout << std::endl << std::endl;
    }
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
    std::string str_of_numbers;
    auto it {InputParser::get_it()}; 
    while(it != buffer.end())
    {
        if(InputParser::is_number(it))
        {
            str_of_numbers += *it;
        }
        else if(*it == '.')
        {
            str_of_numbers += *it;
        }
        else if(*it == ',')
        {
            str_of_numbers += '.';
        }
        else
            break;
        it++;
    }
    InputParser::set_it(it);
    if(str_of_numbers.empty())
        return NOT_NUMBER;
    
    return std::stod(str_of_numbers);
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
    InputParser::set_it(++it);
    return power_sign;
}
