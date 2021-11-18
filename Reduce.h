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
        void remove_term(std::vector<std::vector<struct value>> &vector_of_terms, const unsigned int index);
    public:
        Reduce();
        Reduce(std::vector<std::vector<struct value>> collection_of_expressions);
        ~Reduce();

        //Utility functions
        bool end_of_term(const struct value value);
        bool is_power_of_one(const struct value value);
        struct value create_power_of_one();
        bool exponent_match(const struct value value1, const struct value value2);
        void add_coefficient_of_one(std::vector<struct value> &term);
        bool is_coefficient(const std::vector<struct value> term);
        const struct value update_positive_or_negative(const double result, const struct value value);

        void display_expression();
        void display_values();

        void reduce_expression();

        //Calculation functions

        //Multiplication functions
        void calculate_multiplication();
        void search_fixed_numbers_to_multiply(std::vector<struct value> &expression);
        double multiply_fixed_numbers(const struct value value1, const struct value value2);
        void search_equal_variables_to_multiply(std::vector<struct value> &expression);
        double multiply_equal_variables(const struct value value1, const struct value value2);

        //Division functions
        void calculate_division();
        void search_fixed_numbers_to_divide(std::vector<struct value> &expression);
        double divide_fixed_numbers(const struct value value1, const struct value value2);
        void search_equal_variables_to_divide(std::vector<struct value> &expression);
        double divide_equal_variables(const struct value value1, const struct value value2);

        //Subtraction functions
        void calculate_subtraction();
        void subtract_terms(std::vector<struct value> &expression);
        bool reduce_terms(std::vector<struct value> &result_term, const std::vector<struct value> larger_term, const std::vector<struct value> smaller_term);
        double subtract_fixed_numbers(const struct value value1, const struct value value2);
        double subtract_equal_variables(const struct value value1, const struct value value2);
        std::vector<struct value> init_term(const std::vector<struct value> expression, unsigned int &cur_index, const bool update_index);

};

#endif