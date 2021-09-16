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

struct value InputParser::init_value()
{
    struct value new_value {EMPTY, EMPTY, EMPTY, ZERO};
    return new_value;
}

bool InputParser::parse_buffer()
{
    InputParser::it = buffer.begin();
    struct value value {InputParser::init_value()};

    /*
    In this loop the iterator "it" will iterate through the buffer and
    parse the characters in to a structure. When the structure
    is filled it will be pushed in to a vector.
    */

    while(InputParser::it != buffer.end())
    {
        if(InputParser::is_number(InputParser::it))
        {
            if(InputParser::is_variable(InputParser::it-1))
                value.sign = '*';
            
            if(InputParser::it == buffer.begin())
                value.positive_or_negative = '+';
            
            double number {ZERO};
            if((number = InputParser::parse_numbers()) != ZERO)
            {   
                value.number = number;
            }
        }
        else if(InputParser::is_variable(InputParser::it))
        {
            if(it != buffer.begin())
            {
                if(InputParser::is_number(InputParser::it-1) || InputParser::is_variable(InputParser::it-1))
                    value.sign = '*';
            }
            
            char variable {EMPTY};
            if((variable = InputParser::parse_variables()) != EMPTY)
            {
                value.variable = variable;
            }
        }
        else if(InputParser::is_power_sign(InputParser::it))
        {
            char power_sign {EMPTY};
            if((power_sign = InputParser::parse_power_sign()) != EMPTY)
            {
                value.sign = power_sign;
            }
        }
        else if(InputParser::is_multiplication_sign(InputParser::it))
        {
            char multiplication_sign {EMPTY};
            if((multiplication_sign = InputParser::parse_multiplication_sign()) != EMPTY)
            {
                value.sign = multiplication_sign;
            }
        }
        else if(InputParser::is_division_sign(InputParser::it))
        {
            char division_sign {EMPTY};
            if((division_sign = InputParser::parse_division_sign()) != EMPTY)
            {
                value.sign = division_sign;
            }
        }
        else if(InputParser::is_minus_sign(InputParser::it))
        {
            if(InputParser::is_minus_sign(InputParser::it-1)) //Logic for converting -- to +
            {
                value.positive_or_negative = '+';
                InputParser::set_it(++it);
            }
            else if(InputParser::is_plus_sign(InputParser::it-1)) //Logic for converting +- to -
            {
                value.positive_or_negative = '-';
                InputParser::set_it(++it);
            }
            else
            {
                char minus_sign {EMPTY};
                if((minus_sign = InputParser::parse_minus_sign()) != EMPTY)
                {
                    value.positive_or_negative = minus_sign;
                }
            }
        }
        else if(InputParser::is_plus_sign(InputParser::it))
        {
            if(InputParser::is_minus_sign(InputParser::it-1)) //Logic for converting -+ to -
            {
                value.positive_or_negative = '-';
                InputParser::set_it(++it);
            }
            else
            {
                char plus_sign {EMPTY};
                if((plus_sign = InputParser::parse_plus_sign()) != EMPTY)
                {
                    value.positive_or_negative = plus_sign;
                }
            }
        }
        else
            return false;

        //This will determine if the current struct is ready to be pushed in to a vector
        if(InputParser::value_is_full(value))
        {
            values.push_back(value);
            value = InputParser::init_value();
        }
        
        it = InputParser::get_it();
    }
    return true;
}

bool InputParser::value_is_full(struct value &value)
{
    int counter {0};

    if(value.number != ZERO || value.variable != EMPTY) //If number or variable is found
        counter++;
    
    if(value.sign != EMPTY)
    {
        if(value.positive_or_negative == EMPTY)
            value.positive_or_negative = '+';
    }

    if(value.positive_or_negative != EMPTY)
        counter++;

    if(counter == 2)
        return true;
    
    return false;
}

void InputParser::display_values()
{
    for(auto value: values)
    {
        if(value.positive_or_negative != EMPTY)
            std::cout << "Positive or negative: " << value.positive_or_negative << std::endl;
        if(value.sign != EMPTY)
            std::cout << "Sign: " << value.sign << std::endl;
        if(value.number != ZERO)
            std::cout << "Number: " << value.number << std::endl;
        if(value.variable != EMPTY)
            std::cout << "Variable: " << value.variable << std::endl;
        std::cout << std::endl;
    }
}

bool InputParser::is_number(const std::string::iterator it)
{
    if(*it >= '0' && *it <= '9')
        return true;

    return false;
}

bool InputParser::is_variable(const std::string::iterator it)
{
    if((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z'))
        return true;
    
    return false;
}

bool InputParser::is_power_sign(const std::string::iterator it)
{
    if(*it == '^')
        return true;
    
    return false;
}

bool InputParser::is_multiplication_sign(const std::string::iterator it)
{
    if(*it == '*')
        return true;
    
    return false;
}

bool InputParser::is_division_sign(const std::string::iterator it)
{
    if(*it == '/')
        return true;
    
    return false;
}

bool InputParser::is_minus_sign(const std::string::iterator it)
{
    if(*it == '-')
        return true;
    
    return false;
}

bool InputParser::is_plus_sign(const std::string::iterator it)
{
    if(*it == '+')
        return true;
    
    return false;
}

const double InputParser::parse_numbers()
{
    std::string str_of_numbers {};
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
        return ZERO;
    
    return std::stod(str_of_numbers);
}

const char InputParser::parse_variables()
{
    char variable {EMPTY};
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
    char multiplication_sign {EMPTY};
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
    char plus_sign {EMPTY};
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
    char minus_sign {EMPTY};
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
    char division_sign {EMPTY};
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
    char power_sign {EMPTY};
    auto it {this->get_it()};

    if(it != buffer.end())
    {
        if(InputParser::is_power_sign(it))
            power_sign = *it;
    }
    InputParser::set_it(++it);
    return power_sign;
}
