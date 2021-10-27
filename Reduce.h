#ifndef REDUCE_H
#define REDUCE_H

#include "InputParser.h"
#include <cmath>

class Reduce
{
    private:
        std::vector<std::vector<struct value>> full_expression;

        void remove_element(std::vector<struct value> &vec, const unsigned int position);
    public:
        Reduce();
        Reduce(std::vector<std::vector<struct value>> collection_of_expressions);
        ~Reduce();

        void display_result();
        void display_expressions();

        void reduce_expression();
        void clear_parenthesis();
        void swap_positives_and_negatives_inside_parenthesis(std::vector<struct value> &parenthesis);

        //Calculation functions
        void calculate_power();
        double power_two_numbers(const struct value value1, const struct value value2);

        void calculate_multiplication();
        double multiply_equal_variables(const struct value value1, const struct value value2);
        double multiply_two_numbers(const struct value value1, const struct value value2);

        void calculate_division();
        double divide_equal_variables(const struct value value1, const struct value value2);
        double divide_two_numbers(const struct value value1, const struct value value2);

        void calculate_minus();
        void calculate_plus();
};

#endif