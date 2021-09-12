#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

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

        struct value init_value(struct value value);

        bool parse_buffer();
        bool value_is_full(struct value value);
        void display_values();


        //is_functions
        bool is_number(std::string::iterator it);
        bool is_variable(std::string::iterator it);
        bool is_power_sign(std::string::iterator it);
        bool is_multiplication_sign(std::string::iterator it);
        bool is_division_sign(std::string::iterator it);
        bool is_minus_sign(std::string::iterator it);
        bool is_plus_sign(std::string::iterator it);

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