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

bool Reduce::end_of_term(const struct value value)
{
    if(value.sign == EMPTY)
    {
        if(value.positive_or_negative != EMPTY)
            return true;
    }
    return false;
}

unsigned int Reduce::length_of_term(const std::vector<struct value> expression, const unsigned int start)
{
    unsigned int i {start};
    while(i < expression.size())
    {
        if(end_of_term(expression.at(i)) && i != start)
            break;
        i++;
    }
    return i-start;
}

bool Reduce::is_power_of_one(const struct value value)
{
    if(value.sign == POWER_SIGN)
    {
        if(value.number == 1)
            return true;
    }
    return false;
}

struct value Reduce::create_power_of_one()
{
    struct value power_of_one {PLUS_SIGN, POWER_SIGN, EMPTY, EMPTY, 1, EMPTY, EMPTY};
    return power_of_one;
}

bool Reduce::exponent_match(const struct value value1, const struct value value2)
{
    if(value1.sign == POWER_SIGN && value2.sign == POWER_SIGN)
    {
        if(value1.number != EMPTY && value2.number != EMPTY)
        {
            if(value1.number == value2.number)
                return true;
        }
    }
    return false;
}

void Reduce::add_coefficient_of_one(std::vector<struct value> &term)
{
    if(!is_coefficient(term))
    {
        InputParser parser;
        //Adding coefficient_of_one
        insert_element(term, 0);
        struct value coefficient_of_one {parser.init_value()};
        coefficient_of_one.number = 1;
        coefficient_of_one.positive_or_negative = term.at(1).positive_or_negative;
        term.at(0) = coefficient_of_one;

        //Adding power_of_one
        insert_element(term, 1);
        struct value power_of_one {parser.init_value()};;
        power_of_one.sign = POWER_SIGN;
        power_of_one.number = 1;
        power_of_one.positive_or_negative = PLUS_SIGN;
        term.at(1) = power_of_one;
    }
}

bool Reduce::is_coefficient(const std::vector<struct value> term)
{
    bool is_coefficient {false};
    for(auto value: term)
    {
        if(value.number != ZERO && value.positive_or_negative != EMPTY)
        {
            if(value.sign == EMPTY)
                is_coefficient = true;
        }
    }
    return is_coefficient;
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
    calculate_division();
    calculate_subtraction();
}

void Reduce::calculate_multiplication()
{
    for(auto &expression: full_expression)
    {
        search_equal_variables_to_multiply(expression);
        search_fixed_numbers_to_multiply(expression);
    }
}

void Reduce::search_fixed_numbers_to_multiply(std::vector<struct value> &expression)
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

void Reduce::search_equal_variables_to_multiply(std::vector<struct value> &expression)
{
    for(unsigned int i {0}; i < expression.size(); i++)
    {
        for(unsigned int j {i}; j < expression.size(); j++)
        {
            if(i == j && j < expression.size()-1)
                j++;
            
            /*
            If program encounters end of term.
            Then we increment i at the beginning of the second term and exit the inner loop.
            */
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

void Reduce::calculate_division()
{
    for(auto &expression: full_expression)
    {
        search_fixed_numbers_to_divide(expression);
        search_equal_variables_to_divide(expression);
    }
}

void Reduce::search_fixed_numbers_to_divide(std::vector<struct value> &expression)
{
    for(unsigned int i {0}; i < expression.size(); i++)
    {
        for(unsigned int j {i}; j < expression.size(); j++)
        {
            if(i == j && j < expression.size()-1)
                j++;
            
            if(end_of_term(expression.at(j)))
                break;
            
            if(expression.at(i).number != ZERO && expression.at(j).number != ZERO)
            {
                if(expression.at(j).sign != DIVISION_SIGN)
                    continue;
                if(expression.at(i).sign == POWER_SIGN && expression.size() != 1)
                    continue;
                
                //Division operation
                double result = divide_fixed_numbers(expression.at(i), expression.at(j));
                expression.at(i).number = result;
                expression.at(i) = update_positive_or_negative(result, expression.at(i));
                remove_element(expression, j);
                remove_element(expression, j--);
            }
        }
    }
}

double Reduce::divide_fixed_numbers(const struct value value1, const struct value value2)
{
    double result {0};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = -value1.number / -value2.number;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                || (value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == MINUS_SIGN))
    {
        result = -value1.number / value2.number;
    }
    else
    {
        result = value1.number / value2.number;
    }

    return result;
}

void Reduce::search_equal_variables_to_divide(std::vector<struct value> &expression)
{
    for(unsigned int i {0}; i < expression.size(); i++)
    {
        for(unsigned int j {i}; j < expression.size(); j++)
        {
            if(i == j && j < expression.size()-1)
                j++;
            
            /*
            If program encounters end of term.
            Then we increment i at the beginning of the second term and exit the inner loop.
            */
            if(end_of_term(expression.at(j)))
                break;

            if(expression.at(i).variable != EMPTY && expression.at(j).variable != EMPTY)
            {
                if(expression.at(j).sign != DIVISION_SIGN)
                    continue;
                if(expression.at(i).variable != expression.at(j).variable)
                    continue;
                if(expression.at(i).sign == POWER_SIGN && expression.size() != 1)
                    continue;
                
                double result = divide_equal_variables(expression.at(i), expression.at(j));
                expression.at(i).number = result;
                expression.at(i).variable = EMPTY;
                expression.at(i) = update_positive_or_negative(result, expression.at(i));
                if(expression.at(j).sign == DIVISION_SIGN)
                    expression.at(i+1).number -= expression.at(j+1).number;
                
                remove_element(expression, j);
                remove_element(expression, j--);
            }
        }
    }
}

double Reduce::divide_equal_variables(const struct value value1, const struct value value2)
{
    double result {0};
    double positive_value {1}, negative_value {-1};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = negative_value / negative_value;
    }
    else if((value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
                || (value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == MINUS_SIGN))
    {
        result = positive_value / negative_value;
    }
    else
    {
        result = positive_value / positive_value;
    }
    return result;
}

void Reduce::calculate_subtraction()
{
    for(auto &expression: full_expression)
    {
        subtract_terms(expression);
    }
}

void Reduce::subtract_terms(std::vector<struct value> &expression)
{
    unsigned int cur_index {0};
    while(cur_index < expression.size())
    {
        std::vector<struct value> first_term {init_term(expression, cur_index, true)};
        std::vector<struct value> second_term {init_term(expression, cur_index, false)};

        if(first_term.size() == 0 || second_term.size() == 0)
            return;
        
        add_coefficient_of_one(first_term);
        add_coefficient_of_one(second_term);

        std::vector<struct value> result_term {};

        if(first_term.size() >= second_term.size())
        {
            result_term = reduce_terms(first_term, second_term);
        }
        else if(first_term.size() < second_term.size())
        {
            result_term = reduce_terms(second_term, first_term);
        }

        if(!result_term.empty())
        {
            
            unsigned int start {0};
            start = cur_index-first_term.size();
            size_t end {first_term.size() + second_term.size()};
            update_expression(expression, result_term, start, end);
            break;
        }
    }
}

std::vector<struct value> Reduce::reduce_terms(const std::vector<struct value> larger_term, const std::vector<struct value> smaller_term)
{
    std::vector<struct value> result_term {};
    bool terms_match {false};
    for(unsigned int i {0}; i < larger_term.size(); i++)
    {
        if(is_power_of_one(larger_term.at(i)))
            continue;
        
        for(unsigned int j {0}; j < smaller_term.size(); j++)
        {
            if(is_power_of_one(smaller_term.at(j)))
                continue;
            
            InputParser parser;
            struct value value {parser.init_value()};

            if(larger_term.at(i).number != ZERO && smaller_term.at(j).number != ZERO)
            {
                //If exponents are greater than 1 and both larger_term and smaller_term exponents match
                if(exponent_match(larger_term.at(i), smaller_term.at(j)))
                {
                    result_term.push_back(smaller_term.at(j));
                    terms_match = true;
                    continue;
                }
                
                //If values are not just addition or subtraction
                if(larger_term.at(i).sign != EMPTY || smaller_term.at(j).sign != EMPTY)
                    continue;
                
                //add the coefficient
                value.number = subtract_fixed_numbers(larger_term.at(i), smaller_term.at(j));
                value = update_positive_or_negative(value.number, value);
                result_term.push_back(value);
                terms_match = true;
            }
            else if(larger_term.at(i).variable != EMPTY && smaller_term.at(j).variable != EMPTY)
            {
                //Copy and paste variables to the result term
                if(larger_term.at(i).variable == smaller_term.at(j).variable)
                {
                    value.number = subtract_equal_variables(larger_term.at(i), smaller_term.at(j));
                    value = update_positive_or_negative(value.number, larger_term.at(i));
                    value.variable = smaller_term.at(j).variable;
                    value.number = ZERO;
                    result_term.push_back(value);
                    terms_match = true;
                }
            }
            else
                terms_match = false; //If the terms don´t match
        }
    }
    print_vector(result_term);
    if(terms_match)
    {
        if(result_term.at(0).number == ZERO && result_term.at(0).variable == EMPTY)
        {
            InputParser parser;
            struct value zero {parser.init_value()};
            result_term.clear();
            result_term.push_back(zero);
        }
        std::cout << "Termit matchaa" << std::endl;
    }
    else
    {
        std::cout << "Termit ei matchaa" << std::endl;
        result_term.clear();
    }
    return result_term;
}

double Reduce::subtract_fixed_numbers(const struct value value1, const struct value value2)
{
    double result {0};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = -value1.number -value2.number;
    }
    else if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
    {
        result = -value1.number +value2.number;
    }
    else if(value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = value1.number -value2.number;
    }
    else if(value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
    {
        result = value1.number + value2.number;
    }
    else
    {
        result = value1.number - value2.number;
    }

    return result;
}

double Reduce::subtract_equal_variables(const struct value value1, const struct value value2)
{
    double result {0};
    double positive_value {1}, negative_value {-1};

    if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = negative_value - negative_value; // 0
    }
    else if(value1.positive_or_negative == MINUS_SIGN && value2.positive_or_negative == PLUS_SIGN)
    {
        result = negative_value - positive_value; // -2
    }
    else if(value1.positive_or_negative == PLUS_SIGN && value2.positive_or_negative == MINUS_SIGN)
    {
        result = positive_value - negative_value; // 2
    }
    else
    {
        result = positive_value - positive_value; // 0
    }
    return result;

}

std::vector<struct value> Reduce::init_term(const std::vector<struct value> expression, unsigned int &cur_index, const bool update_index)
{
    std::vector<struct value> term {};
    unsigned int i {cur_index};
    for(; i < expression.size(); i++)
    {
        if(end_of_term(expression.at(i)) && i != cur_index)
            break;
        
        term.push_back(expression.at(i));
    }

    if(update_index)
        cur_index = i;
    
    return term;
}

void Reduce::update_expression(std::vector<struct value> &expression, const std::vector<struct value> result_term, const unsigned int start, const size_t end)
{
    //Kirjoita uudelleen
}