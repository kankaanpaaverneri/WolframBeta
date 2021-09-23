#include "InputParser.h"

InputParser::InputParser()
    : main_buffer {} {}

void InputParser::set_buffer(const std::string buffer)
{
    this->main_buffer = buffer;
}

std::string InputParser::get_buffer()
{
    return this->main_buffer;
}

struct value InputParser::init_value()
{
    struct value new_value {EMPTY, EMPTY, EMPTY, ZERO};
    return new_value;
}

bool InputParser::value_is_empty(const struct value value)
{
    if(value.number == ZERO && value.positive_or_negative == EMPTY && value.sign == EMPTY && value.variable == EMPTY)
    {
        return true;
    }
    return false;
}

bool InputParser::parse_buffer(std::string sub_buffer, std::string::iterator cur_it)
{
    cur_it = sub_buffer.begin();
    struct value value {InputParser::init_value()};

    /*
    In this loop the iterator "it" will iterate through the buffer and
    parse the characters in to a structure. When the structure
    is filled it will be pushed in to a vector.
    */

    while(cur_it != sub_buffer.end())
    {
        if(InputParser::is_number(cur_it))
        {
            value.positive_or_negative = InputParser::add_plus_sign_if_required(sub_buffer, cur_it, value);
            value.sign = InputParser::add_multiplication_if_required(sub_buffer, cur_it, value);
            
            double number {ZERO};
            if((number = InputParser::parse_numbers(sub_buffer, cur_it)) != ZERO)  
                value.number = number;
        }
        else if(InputParser::is_sqrt_sign(cur_it) != ZERO)
        {
            std::cout << "Is sqrt" << std::endl;
        }
        else if(InputParser::is_variable(cur_it))
        {
            value.positive_or_negative = InputParser::add_plus_sign_if_required(sub_buffer, cur_it, value);
            value.sign = InputParser::add_multiplication_if_required(sub_buffer, cur_it, value);
            
            char variable {EMPTY};
            if((variable = InputParser::parse_variable(sub_buffer, cur_it)) != EMPTY)
                value.variable = variable;
        }
        else if(InputParser::is_power_sign(cur_it))
        {
            char power_sign {EMPTY};
            if((power_sign = InputParser::parse_power_sign(sub_buffer, cur_it)) != EMPTY)
                value.sign = power_sign;
        }
        else if(InputParser::is_multiplication_sign(cur_it))
        {
            char multiplication_sign {EMPTY};
            if((multiplication_sign = InputParser::parse_multiplication_sign(sub_buffer, cur_it)) != EMPTY)
                value.sign = multiplication_sign;
        }
        else if(InputParser::is_division_sign(cur_it))
        {
            char division_sign {EMPTY};
            if((division_sign = InputParser::parse_division_sign(sub_buffer, cur_it)) != EMPTY)
            {
                value.sign = division_sign;
            }
        }
        else if(InputParser::is_minus_sign(cur_it))
        {
            value.positive_or_negative = InputParser::convert_double_negative_to_positive(sub_buffer, cur_it, value);
            
            if(value.positive_or_negative == EMPTY)
                value.positive_or_negative = InputParser::convert_positive_negative_to_minus(sub_buffer, cur_it, value);

            if(value.positive_or_negative == EMPTY)
                value.positive_or_negative = InputParser::parse_minus_sign(sub_buffer, cur_it);
        }
        else if(InputParser::is_plus_sign(cur_it))
        {
            value.positive_or_negative = InputParser::convert_positive_negative_to_minus(sub_buffer, cur_it, value);
            
            if(value.positive_or_negative == EMPTY)
                value.positive_or_negative = InputParser::parse_plus_sign(sub_buffer, cur_it);
        }
        else
            return false;

        //This will determine if the current struct is ready to be pushed in to a vector
        if(InputParser::value_is_full(value))
        {
            values.push_back(value);
            value = InputParser::init_value();
        }
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
            value.positive_or_negative = PLUS_SIGN;
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
    if(*it == POWER_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_multiplication_sign(const std::string::iterator it)
{
    if(*it == MULTIPLICATION_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_division_sign(const std::string::iterator it)
{
    if(*it == DIVISION_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_minus_sign(const std::string::iterator it)
{
    if(*it == MINUS_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_plus_sign(const std::string::iterator it)
{
    if(*it == PLUS_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_sqrt_sign(const std::string::iterator it)
{
    std::string::iterator temp_it {it};
    
    unsigned int i {0};
    const unsigned int n {5};

    while(i < n)
    {
        if(*temp_it == example_sqrt_str.at(i))
        {
            temp_it++;
            i++;
        }
        else
            return ZERO;
    }

    return ZERO;
}

bool InputParser::is_open_bracket(const std::string::iterator it)
{
    if(*it == OPEN_BRACKET)
        return true;
    
    return false;
}

bool InputParser::is_closed_bracket(const std::string::iterator it)
{
    if(*it == CLOSED_BRACKET)
        return true;
    
    return false;
}

const double InputParser::parse_numbers(const std::string sub_buffer, std::string::iterator &it)
{
    std::string str_of_numbers {};
    while(it != sub_buffer.end())
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

    if(str_of_numbers.empty())
        return ZERO;
    
    return std::stod(str_of_numbers);
}

const char InputParser::parse_variable(const std::string sub_buffer, std::string::iterator &it)
{
    char variable {EMPTY};

    if(it != sub_buffer.end())
    {
        if(InputParser::is_variable(it))
            variable = *it;
    }
    it++;
    return variable;
}

const char InputParser::parse_multiplication_sign(const std::string sub_buffer, std::string::iterator &it)
{
    char multiplication_sign {EMPTY};
    if(it != sub_buffer.end())
    {
        if(InputParser::is_multiplication_sign(it))
            multiplication_sign = *it;
    }
    it++;
    return multiplication_sign;
}

const char InputParser::parse_plus_sign(const std::string sub_buffer, std::string::iterator &it)
{
    char plus_sign {EMPTY};

    if(it != sub_buffer.end())
    {
        if(InputParser::is_plus_sign(it))
            plus_sign = *it;
    }
    it++;
    return plus_sign;
}

const char InputParser::parse_minus_sign(const std::string sub_buffer, std::string::iterator &it)
{
    char minus_sign {EMPTY};

    if(it != sub_buffer.end())
    {
        if(InputParser::is_minus_sign(it))
            minus_sign = *it;
    }
    it++;
    return minus_sign;
}

const char InputParser::parse_division_sign(const std::string sub_buffer, std::string::iterator &it)
{
    char division_sign {EMPTY};

    if(it != sub_buffer.end())
    {
        if(InputParser::is_division_sign(it))
            division_sign = *it;
    }
    it++;
    return division_sign;
}

const char InputParser::parse_power_sign(const std::string sub_buffer, std::string::iterator &it)
{
    char power_sign {EMPTY};

    if(it != sub_buffer.end())
    {
        if(InputParser::is_power_sign(it))
            power_sign = *it;
    }
    it++;
    return power_sign;
}

const char InputParser::add_multiplication_if_required(const std::string &sub_buffer, const std::string::iterator &cur_it, const struct value &value)
{
    if(cur_it == sub_buffer.begin())    
        return EMPTY;
    
    if(value.sign != EMPTY)
        return value.sign;
    
    if(InputParser::is_number(cur_it) && InputParser::is_variable(cur_it-1))
        return MULTIPLICATION_SIGN;
    else if(InputParser::is_variable(cur_it) && InputParser::is_number(cur_it-1))
        return MULTIPLICATION_SIGN;
    else if(InputParser::is_variable(cur_it) && InputParser::is_variable(cur_it-1))
        return MULTIPLICATION_SIGN;
    
    return EMPTY;
}

const char InputParser::add_plus_sign_if_required(const std::string &sub_buffer, const std::string::iterator &cur_it, const struct value &value)
{
    if(cur_it == sub_buffer.begin())
        return PLUS_SIGN;
    
    if(value.positive_or_negative != EMPTY)
        return value.positive_or_negative;
    
    
    //Need to add some logic if we are in the first character after OPEN_BRACKET
    
    return EMPTY;
}

const char InputParser::convert_double_negative_to_positive(const std::string &sub_buffer, std::string::iterator &cur_it, const struct value &value)
{
    if(cur_it == sub_buffer.begin())
        return EMPTY;

    if(InputParser::is_minus_sign(cur_it) && InputParser::is_minus_sign(cur_it-1))
    {
        cur_it++;
        return PLUS_SIGN;
    }
    
    return EMPTY;
}

const char InputParser::convert_positive_negative_to_minus(const std::string &sub_buffer, std::string::iterator &cur_it, const struct value &value)
{
    if(cur_it == sub_buffer.begin())
        return EMPTY;
    
    if(InputParser::is_minus_sign(cur_it) && InputParser::is_plus_sign(cur_it-1))
    {
        cur_it++;
        return MINUS_SIGN;
    }
    else if(InputParser::is_plus_sign(cur_it) && InputParser::is_minus_sign(cur_it-1))
    {
        cur_it++;
        return MINUS_SIGN;
    }
    return EMPTY;
}