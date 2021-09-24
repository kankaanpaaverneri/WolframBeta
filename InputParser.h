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
    char sign; // *, ^, /, sqrt[]
    char variable; //a-z and A-Z
    double number; //0-9
    char open_bracket, closed_bracket; //[ ]
};

class InputParser
{
    private:
        std::string main_buffer;
        std::vector<std::vector<struct value>> collection_of_expressions;
        const std::string example_sqrt_str {"sqrt["};
    public:
        InputParser();

        void set_buffer(const std::string sub_buffer);
        std::string get_buffer();

        struct value init_value();
        bool is_value_empty(const struct value value);

        bool parse_buffer(std::string buffer, unsigned int &i);
        bool write_in_value(const std::string sub_buffer, unsigned int &i, struct value &value);
        bool is_value_full(struct value &value);
        void display_expressions();


        bool is_number(const char character);
        bool is_variable(const char character);
        bool is_power_sign(const char character);
        bool is_multiplication_sign(const char character);
        bool is_division_sign(const char character);
        bool is_minus_sign(const char character);
        bool is_plus_sign(const char character);
        bool is_open_bracket(const char character);
        bool is_closed_bracket(const char character);

        const double parse_numbers(const std::string sub_buffer, unsigned int &i);
        const char parse_variable(const std::string sub_buffer, unsigned int &i);
        const char parse_plus_sign(const std::string sub_buffer, unsigned int &i);
        const char parse_minus_sign(const std::string sub_buffer, unsigned int &i);
        const char parse_multiplication_sign(const std::string sub_buffer, unsigned int &i);
        const char parse_division_sign(const std::string sub_buffer, unsigned int &i);
        const char parse_power_sign(const std::string sub_buffer, unsigned int &i);

        const char add_multiplication_if_required(const std::string sub_buffer, unsigned int &i, const struct value &value);
        const char add_plus_sign_if_required(const std::string sub_buffer, unsigned int &i, const struct value &value);
        const char convert_double_negative_to_positive(const std::string sub_buffer, unsigned int &i, const struct value &value);
        const char convert_positive_negative_to_minus(const std::string sub_buffer, unsigned int &i, const struct value &value);
};

#endif