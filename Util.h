#ifndef UTIL_H
#define UTIL_H

#include "InputParser.h"

#include <math.h>
#include <vector>

//Utility functions
int convert_binary_to_decimal(long long n);
long long convert_decimal_to_binary(int n);
void print_vector(const std::vector<struct value> vec);

#endif