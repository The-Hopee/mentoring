#include "sum.h"
#include <iostream>

int main()
{
    const auto result = lib::sum(1,2);
    std::cout << "The result is: " << result << "\n";
    return 0;
}