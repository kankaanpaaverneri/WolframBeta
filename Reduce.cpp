#include "Reduce.h"

Reduce::Reduce()
{}

Reduce::Reduce(std::vector<std::vector<struct value>> collection_of_expressions)
    : full_expression {collection_of_expressions} {
}

Reduce::~Reduce()
{}

void Reduce::remove_element(std::vector<struct value> &vec, const unsigned int index)
{
    auto position {vec.begin()};
    position += index;
    vec.erase(position);
}

void Reduce::insert_element(std::vector<struct value> &vec, const unsigned int index)
{
    auto position {vec.begin()};
    position += index;
    InputParser parser;
    struct value new_empty_element {parser.init_value()};
    vec.insert(position, new_empty_element);
}

void Reduce::display_expression()
{
    for(auto sub_expression: full_expression)
    {
        int counter {0};
        for(auto value: sub_expression)
        {
            if(value.positive_or_negative != EMPTY && counter != 0)
            {
                if(value.sign == EMPTY)
                    std::cout << value.positive_or_negative;
            }
            if(value.sign != EMPTY)
            {
                if(value.variable == EMPTY)
                    std::cout << value.sign;
            }
            
            if(value.number != ZERO)
                std::cout << value.number;
            if(value.variable != EMPTY)
                std::cout << value.variable;

            counter++;
        }
    }
    std::cout << std::endl;
}

void Reduce::display_values()
{
    for(auto expression: full_expression)
    {
        std::cout << std::endl << "---------------" << std::endl << std::endl; 
        for(auto value: expression)
        {
            if(value.sign == POWER_SIGN && value.number == 1)
                continue;
            std::cout << std::endl;

            if(value.positive_or_negative != EMPTY)
                std::cout << "Positive or negative: " << value.positive_or_negative << std::endl;
            if(value.sign != EMPTY)
                std::cout << "Sign: " << value.sign << std::endl;
            if(value.number != ZERO)
                std::cout << "Number: " << value.number << std::endl;
            if(value.variable != EMPTY)
                std::cout << "Variable: " << value.variable << std::endl;
            if(value.sqrt_sign != EMPTY)
                std::cout << "sqrt" << std::endl;
            if(value.open_bracket != EMPTY)
                std::cout << "Open bracket: " << value.open_bracket << std::endl;
            if(value.closed_bracket != EMPTY)
                std::cout << "Closed bracket: " << value.closed_bracket << std::endl;
            std::cout << std::endl;
        }
    }
}

void Reduce::reduce_expression()
{
    calculate_multiplication();
}

bool Reduce::end_of_term(const struct value value)
{
    if(value.sign == EMPTY)
    {
        if(value.positive_or_negative != EMPTY)
            return true;
    }
    return false;
}

void Reduce::calculate_multiplication()
{
    for(auto &sub_expression: full_expression)
    {
        search_equal_variables(sub_expression);
        search_fixed_numbers(sub_expression);
    }
}

void Reduce::search_fixed_numbers(std::vector<struct value> &expression)
{
    for(unsigned int i {0}; i < expression.size(); i++)
    {
        for(unsigned int j {i}; j < expression.size(); j++)
        {
            //If j and i are the same and we are not at the end of vector
            if(j == i && j < expression.size()-1)
                j++;
            
            /*
            If program encounters end of term.
            Then we increment i at the beginning of the second term and exit the inner loop.
            */
            if(end_of_term(expression.at(j)))
                break;
            
            if(expression.at(i).number != ZERO && expression.at(j).number != ZERO)
            {   
                if(expression.at(j).sign != MULTIPLICATION_SIGN)
                    continue;
                
                if(expression.at(i).sign == POWER_SIGN && expression.size() != 1)
                    continue;

                //Multiplication operation
                double result = multiply_fixed_numbers(expression.at(i), expression.at(j));
                expression.at(i).number = result;
                expression.at(i) = update_positive_or_negative(result, expression.at(i));
                remove_element(expression, j);
                remove_element(expression, j--);
            }
        }
    }
}

double Reduce::multiply_fixed_numbers(const struct value value1, const struct value value2)
{
    double result {0};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = -value1.number * -value2.number;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                || (value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == MINUS_SIGN))
    {
        result = -value1.number * value2.number;
    }
    else
    {
        result = value1.number * value2.number;
    }

    return result;
}

const struct value Reduce::update_positive_or_negative(const double result, const struct value value)
{
    struct value new_value {value};
    if(result < 0)
    {
        new_value.positive_or_negative = MINUS_SIGN;
        new_value.number = abs(new_value.number);
    }
    else if(result > 0)
        new_value.positive_or_negative = PLUS_SIGN;
    
    return new_value;
}

void Reduce::search_equal_variables(std::vector<struct value> &expression)
{
    for(unsigned int i {0}; i < expression.size(); i++)
    {
        for(unsigned int j {i}; j < expression.size(); j++)
        {
            if(i == j && j < expression.size()-1)
                j++;
            
            if(end_of_term(expression.at(j)))
                break;

            if(expression.at(i).variable != EMPTY && expression.at(j).variable != EMPTY)
            {
                if(expression.at(j).sign != MULTIPLICATION_SIGN)
                    continue;
                if(expression.at(i).variable != expression.at(j).variable)
                    continue;
                if(expression.at(i).sign == POWER_SIGN && expression.size() != 1)
                    continue;
                
                double result = multiply_equal_variables(expression.at(i), expression.at(j));
                expression.at(i) = update_positive_or_negative(result, expression.at(i));
                if(expression.at(j).sign == MULTIPLICATION_SIGN)
                    expression.at(i+1).number += expression.at(j+1).number;
                
                remove_element(expression, j);
                remove_element(expression, j--);
            }
        }
    }
}

double Reduce::multiply_equal_variables(const struct value value1, const struct value value2)
{
    double result {0};
    double positive_value {1}, negative_value {-1};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = negative_value * negative_value;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                || (value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == MINUS_SIGN))
    {
        result = positive_value * negative_value;
    }
    else
    {
        result = positive_value * positive_value;
    }
    return result;
}