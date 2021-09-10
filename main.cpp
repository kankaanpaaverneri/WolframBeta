#include <iostream>
#include "InputParser.h"

int main()
{
    std::cout << "Wolfram Beta" << std::endl;

    std::cout << "Write some input: ";
    std::string buffer;
    std::getline(std::cin, buffer);
    std::cout << buffer << std::endl;
    InputParser parser;
    parser.set_buffer(buffer);
    parser.parse_buffer();
    return 0;
}