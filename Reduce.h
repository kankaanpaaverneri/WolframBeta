#ifndef REDUCE_H
#define REDUCE_H

#include "InputParser.h"
#include <cmath>

class Reduce
{
    private:
        std::vector<std::vector<struct value>> full_expression;
    public:
        Reduce();

        void set_full_expression(const std::vector<std::vector<struct value>> full_expression);
        const std::vector<std::vector<struct value>> get_full_expression() const;

        void remove(const unsigned int start_position, std::vector<struct value> &sub_expression);

        void reduce_expression();
        void calculate_power_operations(std::vector<struct value> &sub_expression);

        void display_result();

        
};

#endif