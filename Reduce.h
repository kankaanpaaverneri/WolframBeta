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

        //Calculation functions
        void calculate_power();
        void calculate_multiplication();
        void calculate_division();
        void calculate_minus();
        void calculate_plus();
};

#endif