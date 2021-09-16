#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include "Util.h"

#include <iostream>
#include <string>
#include <vector>

#define EMPTY 32
#define ZERO 0

struct value
{
    char positive_or_negative; // +, -
    char sign; // *, ^, /, sqrt()
    char variable;
    double number;
};

class InputParser
{
    private:
        std::string buffer;
        std::string::iterator it;
        std::vector<value> values;
    public:
        InputParser();

        void set_buffer(const std::string buffer);
        const std::string get_buffer() const;
        void set_it(std::string::iterator current_iterator);
        const std::string::iterator get_it() const;

        struct value init_value();

        bool parse_buffer();
        bool value_is_full(struct value &value);
        void display_values();


        //is_functions
        bool is_number(const std::string::iterator it);
        bool is_variable(const std::string::iterator it);
        bool is_power_sign(const std::string::iterator it);
        bool is_multiplication_sign(const std::string::iterator it);
        bool is_division_sign(const std::string::iterator it);
        bool is_minus_sign(const std::string::iterator it);
        bool is_plus_sign(const std::string::iterator it);

        //Functions to deal with different characters in the buffer
        const double parse_numbers();
        const char parse_variables();
        const char parse_plus_sign();
        const char parse_minus_sign();
        const char parse_multiplication_sign();
        const char parse_division_sign();
        const char parse_power_sign();
};

#endif