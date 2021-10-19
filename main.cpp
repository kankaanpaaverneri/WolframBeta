#include <iostream>
#include "InputParser.h"
#include "Reduce.h"

int main(int argc, char *argv[])
{
    InputParser parser;

    if(argc == 2)
        parser.set_buffer(argv[1]);
    else
    {
        std::cout << "Write an expression: ";
        std::string buffer {};
        std::cin >> buffer;
        parser.set_buffer(buffer);
    }

    unsigned int i {0};
    if(parser.parse_buffer(parser.get_buffer(), i))
    {
        parser.display_expressions();
        Reduce reducer(parser.get_collection_of_expressions());
        reducer.display_result();
        reducer.calculate_minus();
        reducer.display_expressions();
    }
    else
    {
        std::cout << "Error parsing the buffer" << std::endl;
    }
    
    return 0;
}