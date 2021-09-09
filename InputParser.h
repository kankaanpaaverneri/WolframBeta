#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <iostream>
#include <string>

class InputParser
{
    private:
        std::string buffer;
        size_t position;
    public:
        InputParser();

        void set_buffer(const std::string buffer);
        const std::string get_buffer() const;

        //Functions to deal with different characters in the buffer
        double parse_numbers();
        
};

#endif