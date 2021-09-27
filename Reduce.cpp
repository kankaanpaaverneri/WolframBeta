#include "Reduce.h"

Reduce::Reduce()
{}

void Reduce::set_full_expression(const std::vector<std::vector<struct value>> full_expression)
{
    this->full_expression = full_expression;
}

const std::vector<std::vector<struct value>> Reduce::get_full_expression() const
{
    return this->full_expression;
}

namespace my
{
    void remove(const unsigned int start_position, std::vector<struct value> &sub_expression)
    {
        for(unsigned int i {start_position}; i != sub_expression.size()-1; i++)
        {
            sub_expression.at(i) = sub_expression.at(i+1);
        }
    }
};

void Reduce::reduce_expression()
{
    for(auto sub_expression: full_expression)
    {
        for(auto i {sub_expression.begin()}; i != sub_expression.end(); i++)
        {
            //Calculate the value and result will be put inside the first value and the second value is removed
            Reduce::calculate_power_operations(sub_expression);
            //Calculate multiplication and division
            //Calculate plus and minus
            //Save result
        }
    }
}

void Reduce::calculate_power_operations(std::vector<struct value> &sub_expression)
{
    for(unsigned int i {0}; i != sub_expression.size(); i++)
    {
        //Calculate value and the result will be put inside the first value and the second value is removed
        for(unsigned int j {i+1}; j != sub_expression.size(); j++)
        {
            if(sub_expression.at(i).variable != EMPTY || sub_expression.at(j).variable != EMPTY)
                return;
        
            if(sub_expression.at(j).sign == POWER_SIGN)
            {
                double result = pow(sub_expression.at(i).number, sub_expression.at(j).number);
                sub_expression.at(i).number = result;
                my::remove(j, sub_expression);
            }
        }
    }
}

void Reduce::display_result()
{
    bool first_number = {true};
    for(auto sub_expression: full_expression)
    {
        for(auto value: sub_expression)
        {
            if(value.sign == MULTIPLICATION_SIGN)
            {
                if(value.variable == EMPTY)
                {
                    std::cout << value.sign;
                }
            }
            else
            {
                std::cout << value.sign;
            }
            if(value.positive_or_negative != EMPTY && first_number != true && value.sign == EMPTY)
                std::cout << value.positive_or_negative;
            if(value.number != EMPTY && value.variable == EMPTY)
                std::cout << value.number;
            if(value.variable != EMPTY)
                std::cout << value.variable;
            
            first_number = false;
        }
    }
    std::cout << std::endl << std::endl;
}