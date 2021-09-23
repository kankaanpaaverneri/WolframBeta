#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include "Util.h"

#include <iostream>
#include <string>
#include <vector>

#define EMPTY ' '
#define ZERO 0

#define PLUS_SIGN '+'
#define MINUS_SIGN '-'
#define MULTIPLICATION_SIGN '*'
#define DIVISION_SIGN '/'
#define POWER_SIGN '^'
#define OPEN_BRACKET '['
#define CLOSED_BRACKET ']'

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
        std::string main_buffer;
        std::vector<struct value> values;
        const std::string example_sqrt_str {"sqrt["};
    public:
        InputParser();

        void set_buffer(const std::string sub_buffer);
        std::string get_buffer();

        struct value init_value();
        bool value_is_empty(const struct value value);

        bool parse_buffer(std::string buffer, std::string::iterator cur_it);
        bool value_is_full(struct value &value);
        void display_values();


        bool is_number(const std::string::iterator it);
        bool is_variable(const std::string::iterator it);
        bool is_power_sign(const std::string::iterator it);
        bool is_multiplication_sign(const std::string::iterator it);
        bool is_division_sign(const std::string::iterator it);
        bool is_minus_sign(const std::string::iterator it);
        bool is_plus_sign(const std::string::iterator it);
        bool is_sqrt_sign(const std::string::iterator it);
        bool is_open_bracket(const std::string::iterator it);
        bool is_closed_bracket(const std::string::iterator it);

        const double parse_numbers(const std::string sub_buffer, std::string::iterator &it);
        const char parse_variable(const std::string sub_buffer, std::string::iterator &it);
        const char parse_plus_sign(const std::string sub_buffer, std::string::iterator &it);
        const char parse_minus_sign(const std::string sub_buffer, std::string::iterator &it);
        const char parse_multiplication_sign(const std::string sub_buffer, std::string::iterator &it);
        const char parse_division_sign(const std::string sub_buffer, std::string::iterator &it);
        const char parse_power_sign(const std::string sub_buffer, std::string::iterator &it);

        const char add_multiplication_if_required(const std::string &sub_buffer, const std::string::iterator &cur_it, const struct value &value);
        const char add_plus_sign_if_required(const std::string &sub_buffer, const std::string::iterator &cur_it, const struct value &value);
        const char convert_double_negative_to_positive(const std::string &sub_buffer, std::string::iterator &cur_it, const struct value &value);
        const char convert_positive_negative_to_minus(const std::string &sub_buffer, std::string::iterator &cur_it, const struct value &value);
};

#endif