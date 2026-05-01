#pragma once

namespace math
{
    inline int add(int a, int b)
    {
        return a + b;
    }

    inline int subtract(int a, int b)
    {
        return a - b;
    }

    inline int multiply(int a, int b)
    {
        return a * b;
    }

    inline int divide(int a, int b)
    {
        if (b == 0)
        {
            throw "Division by zero is not allowed.";
        }
        return a / b;
    }

    inline int pow(int a, int b)
    {
        if (b < 0)
        {
            throw "Negative exponent is not supported.";
        }

        int result = 1;
        for (int i = 0; i < b; i++)
        {
            result *= a;
        }
        return result;
    }

    inline int factorial(int a)
    {
        if (a < 0)
        {
            throw "Factorial is not defined for negative numbers.";
        }

        if (a == 0 || a == 1)
        {
            return 1;
        }

        return a * factorial(a - 1);
    }
}
