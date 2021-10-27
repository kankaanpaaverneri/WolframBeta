#include "Reduce.h"

Reduce::Reduce()
{}

Reduce::Reduce(std::vector<std::vector<struct value>> collection_of_expressions)
    : full_expression {collection_of_expressions} {
}

Reduce::~Reduce()
{}

void Reduce::remove_element(std::vector<struct value> &vec, const unsigned int position)
{
    auto it {vec.begin()};
    it += position;
    vec.erase(it);
}

void Reduce::display_result()
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

void Reduce::display_expressions()
{
    for(auto expression: full_expression)
    {
        std::cout << std::endl << "---------------" << std::endl << std::endl; 
        for(auto value: expression)
        {
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
    Reduce::clear_parenthesis();
}

void Reduce::clear_parenthesis()
{
    //This function reduces the full expression
    for(unsigned int i = full_expression.size()-1; i > 0; i--)
    {
        auto sub_expression {full_expression.at(i)};
        for(unsigned int j {0}; j < sub_expression.size(); j++)
        {
            if(sub_expression.at(j).open_bracket == OPEN_BRACKET && sub_expression.at(j).closed_bracket == CLOSED_BRACKET)
            {
                if(sub_expression.at(j).positive_or_negative == MINUS_SIGN)
                {
                    if(i > 0)
                    {
                        swap_positives_and_negatives_inside_parenthesis(full_expression.at(i-1));
                        //Reduce the expression inside parenthesis and put the result in the current element
                    }
                }
            }
        }
    }
}

void Reduce::swap_positives_and_negatives_inside_parenthesis(std::vector<struct value> &parenthesis)
{
    for(unsigned int i {0}; i < parenthesis.size(); i++)
    {
        if(parenthesis.at(i).sign == EMPTY || parenthesis.at(i).sqrt_sign == EMPTY)
        {
            if(parenthesis.at(i).positive_or_negative == PLUS_SIGN)
            {
                parenthesis.at(i).positive_or_negative = MINUS_SIGN;
            }
            else if(parenthesis.at(i).positive_or_negative == MINUS_SIGN)
            {
                parenthesis.at(i).positive_or_negative = PLUS_SIGN;
            }
        }
    }
}

void Reduce::calculate_power()
{
    unsigned int i {0};
    unsigned int j {i+1};
    for(auto &sub_expression: full_expression)
    {
        if(sub_expression.at(i).number != ZERO && sub_expression.at(j).number != ZERO) //Check if both elements have double variables
        {
            if(sub_expression.at(j).sign == POWER_SIGN) // Check if j element has a POWER_SIGN
            {
                double result = power_two_numbers(sub_expression.at(i), sub_expression.at(j));
                sub_expression.at(i).number = result;
                remove_element(sub_expression, j);
            }
        }
    }
}

double Reduce::power_two_numbers(const struct value value1, const struct value value2)
{
    double result {0};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = pow(-value1.number, -value2.number);
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                                                        || (value2.positive_or_negative == MINUS_SIGN && value1.positive_or_negative == PLUS_SIGN))
    {
        result = pow(-value1.number, value2.number);
    }
    else
    {
        result = pow(value1.number, value2.number);
    }
    
    return result;
}

void Reduce::calculate_multiplication()
{
    unsigned int i {0};
    unsigned int j {i+1};

    for(auto &sub_expression: full_expression)
    {
        if(j >= sub_expression.size())
        {
            std::cout << "Returned" << std::endl;
            return;
        }
        
        if(sub_expression.at(i).number != ZERO && sub_expression.at(j).number != ZERO) //Check if both elements have double variables
        {
            if(sub_expression.at(j).sign == MULTIPLICATION_SIGN) // Check if j element has a MULTIPLICATION_SIGN
            {
                double result = multiply_two_numbers(sub_expression.at(i), sub_expression.at(j));

                if(result < 0)
                {
                    sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                    result = abs(result);
                }
                else if(result > 0)
                {
                    sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                }

                sub_expression.at(i).number = result;
                remove_element(sub_expression, j);
            }
        }
        else if(sub_expression.at(i).variable != EMPTY && sub_expression.at(j).variable != EMPTY)
        {
            if(sub_expression.at(j).sign == MULTIPLICATION_SIGN)
            {
                if(sub_expression.at(i).variable == sub_expression.at(j).variable)
                {
                    double result = multiply_equal_variables(sub_expression.at(i), sub_expression.at(j));

                    if(result < 0)
                    {
                        sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                        result = abs(result);
                    }
                    else if(result > 0)
                    {
                        sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                    }

                    sub_expression.at(j).positive_or_negative = PLUS_SIGN;
                    sub_expression.at(j).number += 2;
                    sub_expression.at(j).variable = EMPTY;
                    sub_expression.at(j).sign = POWER_SIGN;
                }
            }
        }
        else if(sub_expression.at(j).sign == POWER_SIGN && sub_expression.at(j).number != EMPTY) //If i element contains power sign and a number
        {
            if(j < sub_expression.size()-1)
            {
                if(sub_expression.at(i).variable == sub_expression.at(j+1).variable) //If variables are equal
                {
                    if(sub_expression.at(j+1).sign == MULTIPLICATION_SIGN)
                    {
                        double result = multiply_equal_variables(sub_expression.at(i), sub_expression.at(j+1));

                        if(result < 0)
                        {
                            sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                            result = abs(result);
                        }
                        else if(result > 0)
                        {
                            sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                        }

                        remove_element(sub_expression, j+1);
                        sub_expression.at(j).number++;
                    }
                }
            }
        }
    }
}

double Reduce::multiply_equal_variables(const struct value value1, const struct value value2)
{
    double result {0};
    const double negative_value {-1}, positive_value {1};
    
    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = negative_value * negative_value;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                                                        || (value2.positive_or_negative == MINUS_SIGN && value1.positive_or_negative == PLUS_SIGN))
    {
        result = positive_value * negative_value;
    }
    else
    {
        result = positive_value * positive_value;
    }

    return result;
}

double Reduce::multiply_two_numbers(const struct value value1, const struct value value2)
{
    double result {0};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = -value1.number * -value2.number;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                                                        || (value2.positive_or_negative == MINUS_SIGN && value1.positive_or_negative == PLUS_SIGN))
    {
        result = value1.number * -value2.number;
    }
    else
    {
        result = value1.number * value2.number;
    }

    return result;
}

void Reduce::calculate_division()
{
    unsigned int i {0};
    unsigned int j {i+1};
    for(auto &sub_expression: full_expression)
    {
        if(sub_expression.at(i).number != ZERO && sub_expression.at(j).number != ZERO) //If we are dividing numbers
        {
            if(sub_expression.at(j).sign == DIVISION_SIGN) // Check if j element has a DIVISON_SIGN
            {
                double result {0};
                result = divide_two_numbers(sub_expression.at(i), sub_expression.at(j));

                if(result < 0)
                {
                    sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                    result = abs(result);
                }
                else if(result > 0)
                {
                    sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                }

                sub_expression.at(i).number = result;
                remove_element(sub_expression, j);
            }
        }
        else if(sub_expression.at(i).variable != EMPTY && sub_expression.at(j).variable != EMPTY) // If we are dividing equal variables
        {
            if(sub_expression.at(j).sign == DIVISION_SIGN)
            {
                if(sub_expression.at(i).variable == sub_expression.at(j).variable) //if variables are the same
                {
                    double result {0};
                    result = divide_equal_variables(sub_expression.at(i), sub_expression.at(j));
                    
                    if(result < 0)
                    {
                        sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                        result = abs(result);
                    }
                    else if(result > 0)
                    {
                        sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                    }

                    sub_expression.at(i).variable = EMPTY;
                    sub_expression.at(i).number = result;
                    remove_element(sub_expression, j);
                }
            }
        }
    }
}

double Reduce::divide_equal_variables(const struct value value1, const struct value value2)
{
    double result {0};
    const double negative_value {-1}, positive_value {1};
    
    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = negative_value / negative_value;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                                                        || (value2.positive_or_negative == MINUS_SIGN && value1.positive_or_negative == PLUS_SIGN))
    {
        result = positive_value / negative_value;
    }
    else
    {
        result = positive_value / positive_value;
    }

    return result;
}

double Reduce::divide_two_numbers(const struct value value1, const struct value value2)
{
    double result {0};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = -value1.number / -value2.number;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                                                        || (value2.positive_or_negative == MINUS_SIGN && value1.positive_or_negative == PLUS_SIGN))
    {
        result = value1.number / -value2.number;
    }
    else
    {
        result = value1.number / value2.number;
    }

    return result;
}

void Reduce::calculate_minus()
{
    unsigned int i {0};
    unsigned int j {i+1};
    for(auto &sub_expression: full_expression)
    {
        if(sub_expression.at(i).number != ZERO && sub_expression.at(j).number != ZERO) //Check if both elements have double variables
        {
            if(sub_expression.at(j).positive_or_negative == MINUS_SIGN) // Check if j element has a MINUS_SIGN
            {
                double result = sub_expression.at(i).number - sub_expression.at(j).number;

                if(result < 0)
                {
                    sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                    result = abs(result);
                }
                else if(result > 0)
                {
                    sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                }
                
                sub_expression.at(i).number = result;
                remove_element(sub_expression, j); //Removes element from the vector at j index
            }
        }
    }
}

void Reduce::calculate_plus()
{
    unsigned int i {0};
    unsigned int j {i+1};
    for(auto &sub_expression: full_expression)
    {
        if(sub_expression.at(i).number != ZERO && sub_expression.at(j).number != ZERO) //Check if both elements have double variables
        {
            if(sub_expression.at(j).positive_or_negative == PLUS_SIGN) // Check if j element has a PLUS_SIGN
            {
                double result = sub_expression.at(i).number + sub_expression.at(j).number;

                if(result < 0)
                {
                    sub_expression.at(i).positive_or_negative = MINUS_SIGN;
                    result = abs(result);
                }
                else if(result > 0)
                {
                    sub_expression.at(i).positive_or_negative = PLUS_SIGN;
                }

                sub_expression.at(i).number = result;
                remove_element(sub_expression, j);
            }
        }
    }
}