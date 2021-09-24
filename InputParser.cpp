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
    struct value new_value {EMPTY, EMPTY, EMPTY, ZERO, EMPTY, EMPTY};
    return new_value;
}

bool InputParser::is_value_empty(const struct value value)
{
    if(value.number == ZERO && value.positive_or_negative == EMPTY && value.sign == EMPTY && value.variable == EMPTY)
    {
        return true;
    }
    return false;
}

bool InputParser::parse_buffer(const std::string sub_buffer, unsigned int &i)
{
    struct value value {InputParser::init_value()};
    std::vector<struct value> expression;

    /*
    In this function we iterate through the sub_buffer and parse the data into a structure "value".
    If the function encounters '[' character. The function will call it self recursively.
    If the function encounters ']' character. The function will exit pushing the current local vector "expression"
    into a "collection_of_expressions".
    */

    while(i != sub_buffer.size())
    {
        //Function will parse the data from the buffer one character at a time.
        if(InputParser::write_in_value(sub_buffer, i, value) == false)
            return false;

        //This will determine if the current struct value "value" is ready to be pushed in to a vector "expression"
        if(InputParser::is_value_full(value))
        {
            expression.push_back(value);
            value = InputParser::init_value();
        }
        
        if(value.closed_bracket == CLOSED_BRACKET)
        {
            break;
        }
    }

    collection_of_expressions.push_back(expression);
    return true;
}
bool InputParser::write_in_value(const std::string sub_buffer, unsigned int &i, struct value &value)
{
    if(InputParser::is_number(sub_buffer.at(i)))
    {
        value.positive_or_negative = InputParser::add_plus_sign_if_required(sub_buffer, i, value);
        value.sign = InputParser::add_multiplication_if_required(sub_buffer, i, value);
        
        double number {ZERO};
        if((number = InputParser::parse_numbers(sub_buffer, i)) != ZERO)  
            value.number = number;
    }
    else if(InputParser::is_variable(sub_buffer.at(i)))
    {
        value.positive_or_negative = InputParser::add_plus_sign_if_required(sub_buffer, i, value);
        value.sign = InputParser::add_multiplication_if_required(sub_buffer, i, value);
      
        char variable {EMPTY};
        if((variable = InputParser::parse_variable(sub_buffer, i)) != EMPTY)
            value.variable = variable;
    }
    else if(InputParser::is_power_sign(sub_buffer.at(i)))
    {
        char power_sign {EMPTY};
        if((power_sign = InputParser::parse_power_sign(sub_buffer, i)) != EMPTY)
            value.sign = power_sign;
    }
    else if(InputParser::is_multiplication_sign(sub_buffer.at(i)))
    {
        char multiplication_sign {EMPTY};
        if((multiplication_sign = InputParser::parse_multiplication_sign(sub_buffer, i)) != EMPTY)
            value.sign = multiplication_sign;
    }
    else if(InputParser::is_division_sign(sub_buffer.at(i)))
    {
        char division_sign {EMPTY};
        if((division_sign = InputParser::parse_division_sign(sub_buffer, i)) != EMPTY)
        {
            value.sign = division_sign;
        }
    }
    else if(InputParser::is_minus_sign(sub_buffer.at(i)))
    {
        value.positive_or_negative = InputParser::convert_double_negative_to_positive(sub_buffer, i, value);
        
        if(value.positive_or_negative == EMPTY)
            value.positive_or_negative = InputParser::convert_positive_negative_to_minus(sub_buffer, i, value);

        if(value.positive_or_negative == EMPTY)
            value.positive_or_negative = InputParser::parse_minus_sign(sub_buffer, i);
    }
    else if(InputParser::is_plus_sign(sub_buffer.at(i)))
    {
        value.positive_or_negative = InputParser::convert_positive_negative_to_minus(sub_buffer, i, value);
            
        if(value.positive_or_negative == EMPTY)
            value.positive_or_negative = InputParser::parse_plus_sign(sub_buffer, i);
    }
    else if(InputParser::is_open_bracket(sub_buffer.at(i)))
    {
        value.open_bracket = OPEN_BRACKET;
        if(InputParser::parse_buffer(sub_buffer, ++i) == false)
            return false;
        
        value.closed_bracket = CLOSED_BRACKET;
    }
    else if(InputParser::is_closed_bracket(sub_buffer.at(i)))
    {
        value.closed_bracket = CLOSED_BRACKET;
        i++;
    }
    else
        return false;
    
    return true;
}

bool InputParser::is_value_full(struct value &value)
{
    int counter {0};

    if(value.open_bracket == OPEN_BRACKET && value.closed_bracket == CLOSED_BRACKET) //If open_bracket and a closed_bracket is found
        return true;

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

void InputParser::display_expressions()
{
    for(auto expression: collection_of_expressions)
    {
        std::cout << std::endl << "Switch vector: " << std::endl << std::endl; 
        for(auto value: expression)
        {
            if(value.positive_or_negative != EMPTY)
                std::cout << "Positive or negative: " << value.positive_or_negative << std::endl;
            if(value.sign != EMPTY)
                std::cout << "Sign: " << value.sign << std::endl;
            if(value.number != ZERO)
                std::cout << "Number: " << value.number << std::endl;
            if(value.variable != EMPTY)
                std::cout << "Variable: " << value.variable << std::endl;
            if(value.open_bracket != EMPTY)
                std::cout << "Open bracket: " << value.open_bracket << std::endl;
            if(value.closed_bracket != EMPTY)
                std::cout << "Closed bracket: " << value.closed_bracket << std::endl;
            std::cout << std::endl;
        }
    }
}

bool InputParser::is_number(const char character)
{
    if(character >= '0' && character <= '9')
        return true;

    return false;
}

bool InputParser::is_variable(const char character)
{
    if((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
        return true;
    
    return false;
}

bool InputParser::is_power_sign(const char character)
{
    if(character == POWER_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_multiplication_sign(const char character)
{
    if(character == MULTIPLICATION_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_division_sign(const char character)
{
    if(character == DIVISION_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_minus_sign(const char character)
{
    if(character == MINUS_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_plus_sign(const char character)
{
    if(character == PLUS_SIGN)
        return true;
    
    return false;
}

bool InputParser::is_open_bracket(const char character)
{
    if(character == OPEN_BRACKET)
        return true;

    return false;
}

bool InputParser::is_closed_bracket(const char character)
{
    if(character == CLOSED_BRACKET)
        return true;
    
    return false;
}

const double InputParser::parse_numbers(const std::string sub_buffer, unsigned int &i)
{
    std::string str_of_numbers {};
    while(i != sub_buffer.size())
    {
        if(InputParser::is_number(sub_buffer.at(i)))
        {
            str_of_numbers += sub_buffer.at(i);
        }
        else if(sub_buffer.at(i) == '.')
        {
            str_of_numbers += sub_buffer.at(i);
        }
        else if(sub_buffer.at(i) == ',')
        {
            str_of_numbers += '.';
        }
        else
            break;
        i++;
    }

    if(str_of_numbers.empty())
        return ZERO;
    
    return std::stod(str_of_numbers);
}

const char InputParser::parse_variable(const std::string sub_buffer, unsigned int &i)
{
    char variable {EMPTY};

    if(i != sub_buffer.size())
    {
        if(InputParser::is_variable(sub_buffer.at(i)))
            variable = sub_buffer.at(i);
    }
    i++;
    return variable;
}

const char InputParser::parse_multiplication_sign(const std::string sub_buffer, unsigned int &i)
{
    char multiplication_sign {EMPTY};
    if(i != sub_buffer.size())
    {
        if(InputParser::is_multiplication_sign(sub_buffer.at(i)))
            multiplication_sign = sub_buffer.at(i);
    }
    i++;
    return multiplication_sign;
}

const char InputParser::parse_plus_sign(const std::string sub_buffer, unsigned int &i)
{
    char plus_sign {EMPTY};

    if(i != sub_buffer.size())
    {
        if(InputParser::is_plus_sign(sub_buffer.at(i)))
            plus_sign = sub_buffer.at(i);
    }
    i++;
    return plus_sign;
}

const char InputParser::parse_minus_sign(const std::string sub_buffer, unsigned int &i)
{
    char minus_sign {EMPTY};

    if(i != sub_buffer.size())
    {
        if(InputParser::is_minus_sign(sub_buffer.at(i)))
            minus_sign = sub_buffer.at(i);
    }
    i++;
    return minus_sign;
}

const char InputParser::parse_division_sign(const std::string sub_buffer, unsigned int &i)
{
    char division_sign {EMPTY};

    if(i != sub_buffer.size())
    {
        if(InputParser::is_division_sign(sub_buffer.at(i)))
            division_sign = sub_buffer.at(i);
    }
    i++;
    return division_sign;
}

const char InputParser::parse_power_sign(const std::string sub_buffer, unsigned int &i)
{
    char power_sign {EMPTY};

    if(i != sub_buffer.size())
    {
        if(InputParser::is_power_sign(sub_buffer.at(i)))
            power_sign = sub_buffer.at(i);
    }
    i++;
    return power_sign;
}

const char InputParser::add_multiplication_if_required(const std::string sub_buffer, unsigned int &i, const struct value &value)
{
    if(i == ZERO)
        return EMPTY;
    
    if(value.sign != EMPTY)
        return value.sign;
    
    if(InputParser::is_number(sub_buffer.at(i)) && InputParser::is_variable(sub_buffer.at(i-1)))
        return MULTIPLICATION_SIGN;
    else if(InputParser::is_variable(sub_buffer.at(i)) && InputParser::is_number(sub_buffer.at(i-1)))
        return MULTIPLICATION_SIGN;
    else if(InputParser::is_variable(sub_buffer.at(i)) && InputParser::is_variable(sub_buffer.at(i-1)))
        return MULTIPLICATION_SIGN;
    
    return EMPTY;
}

const char InputParser::add_plus_sign_if_required(const std::string sub_buffer, unsigned int &i, const struct value &value)
{
    //Adds a PLUS_SIGN to the value if iterator is at the beginning of an expression or at the beginning of a open_bracket
    if(i == ZERO || sub_buffer.at(i-1) == OPEN_BRACKET)
        return PLUS_SIGN;
    
    if(value.positive_or_negative != EMPTY)
        return value.positive_or_negative;
    
    return EMPTY;
}

const char InputParser::convert_double_negative_to_positive(const std::string sub_buffer, unsigned int &i, const struct value &value)
{
    if(i == ZERO || sub_buffer.at(i-1) == OPEN_BRACKET)
        return EMPTY;

    if(InputParser::is_minus_sign(sub_buffer.at(i)) && InputParser::is_minus_sign(sub_buffer.at(i-1)))
    {
        i++;
        return PLUS_SIGN;
    }
    
    return EMPTY;
}

const char InputParser::convert_positive_negative_to_minus(const std::string sub_buffer, unsigned int &i, const struct value &value)
{
    if(i == ZERO || sub_buffer.at(i-1) == OPEN_BRACKET)
        return EMPTY;
    
    if(InputParser::is_minus_sign(sub_buffer.at(i)) && InputParser::is_plus_sign(sub_buffer.at(i-1)))
    {
        i++;
        return MINUS_SIGN;
    }
    else if(InputParser::is_plus_sign(sub_buffer.at(i)) && InputParser::is_minus_sign(sub_buffer.at(i-1)))
    {
        i++;
        return MINUS_SIGN;
    }
    return EMPTY;
}