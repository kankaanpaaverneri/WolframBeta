#include <iostream>
#include "InputParser.h"

int main(int argc, char *argv[])
{
    InputParser parser;

    if(argc == 2)
        parser.set_buffer(argv[1]);
    
    if(parser.parse_buffer(parser.get_buffer(), parser.get_buffer().begin()))
        parser.display_values();
    else
    {
        std::cout << "Error parsing the buffer" << std::endl;
    }
    
    return 0;
}