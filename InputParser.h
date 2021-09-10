#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <iostream>
#include <string>

class InputParser
{
    private:
        std::string buffer;
        std::string::iterator it;
    public:
        InputParser();

        void set_buffer(const std::string buffer);
        const std::string get_buffer() const;
        void set_it(std::string::iterator current_iterator);
        const std::string::iterator get_it() const;

        //Functions to deal with different characters in the buffer
        const double parse_numbers();
        const char parse_variables();
        
};

#endif