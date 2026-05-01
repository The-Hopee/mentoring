#pragma once
#include <climits>

namespace math
{
    inline int add(int a, int b)
    {
        // Проверка переполнения при сложении
        if (b > 0 && a > INT_MAX - b)
        {
            throw "Integer overflow: addition result exceeds INT_MAX.";
        }
        if (b < 0 && a < INT_MIN - b)
        {
            throw "Integer overflow: addition result is less than INT_MIN.";
        }
        return a + b;
    }

    inline int subtract(int a, int b)
    {
        // Проверка переполнения при вычитании
        if (b > 0 && a < INT_MIN + b)
        {
            throw "Integer overflow: subtraction result is less than INT_MIN.";
        }
        if (b < 0 && a > INT_MAX + b)
        {
            throw "Integer overflow: subtraction result exceeds INT_MAX.";
        }
        return a - b;
    }

    inline int multiply(int a, int b)
    {
        // Проверка переполнения при умножении
        if (a != 0 && b != 0)
        {
            if ((b > 0 && a > INT_MAX / b) || (b > 0 && a < INT_MIN / b))
            {
                throw "Integer overflow: multiplication result exceeds int limits.";
            }
            if ((b < 0 && a < INT_MAX / b) || (b < 0 && a > INT_MIN / b))
            {
                throw "Integer overflow: multiplication result exceeds int limits.";
            }
        }
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
            // Проверка переполнения при умножении
            if (a != 0 && result != 0)
            {
                if ((a > 0 && result > INT_MAX / a) || (a < 0 && result < INT_MIN / a))
                {
                    throw "Integer overflow: pow result exceeds int limits.";
                }
            }
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

        int prev = factorial(a - 1);
        
        // Проверка переполнения при умножении
        if (a != 0 && prev != 0)
        {
            if (prev > INT_MAX / a)
            {
                throw "Integer overflow: factorial result exceeds int limits.";
            }
        }
        
        return a * prev;
    }
}
