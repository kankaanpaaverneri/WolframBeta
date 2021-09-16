#include "Util.h"

int convert_binary_to_decimal(long long n)
{
    int decimal_number {0}, i {0}, remainder {0};

    while(n != 0)
    {
        remainder = n % 10;
        n = n / 10;
        decimal_number += remainder * pow(2, i);
        i++;
    }
    return decimal_number;
}

long long convert_decimal_to_binary(int n)
{
    long long binary_number {0};
    int remainder {0}, i {1};

    while(n != 0)
    {
        remainder = n%2;
        n = n / 2;
        binary_number += remainder * i;
        i = i * 10;
    }
    return binary_number;
}