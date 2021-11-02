#ifndef REDUCE_H
#define REDUCE_H

#include "InputParser.h"
#include <cmath>

class Reduce
{
    private:
        std::vector<std::vector<struct value>> full_expression;

        void remove_element(std::vector<struct value> &vec, const unsigned int index);
        void insert_element(std::vector<struct value> &vec, const unsigned int index);
    public:
        Reduce();
        Reduce(std::vector<std::vector<struct value>> collection_of_expressions);
        ~Reduce();

        void display_expression();
        void display_values();

        void reduce_expression();

        //Utility functions
        bool end_of_term(const struct value value);

        //Calculation functions
        void calculate_multiplication();
        void search_fixed_numbers(std::vector<struct value> &expression);
        double multiply_fixed_numbers(const struct value value1, const struct value value2);
        const struct value update_positive_or_negative(const double result, const struct value value);
        double multiply_equal_variables(const struct value value1, const struct value value2);
};

#endif