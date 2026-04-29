#include "interface.h"
#include <math.h>
#include <string.h>

namespace interface
{
    void run(int num1, int num2, const char* operator_)
    {
        Task task;
        task.num1 = num1;
        task.num2 = num2;
        task.operator_ = operator_;
        task.status = 1; // default to error
        makeTask(task);
        makeCalculate(task);
        printResult(task);

        return;
    }

    void makeTask(Task task)
    {
        if( strcmp(task.operator_, "!") == 0 )
        {
            printf("Task created: %d %s\n", task.num1, task.operator_);
            return;
        }
        printf("Task created: %d %s %d\n", task.num1, task.operator_, task.num2);
        return;
    }

    void makeCalculate( Task& task )
    {
        int ans = 0;

        switch(*task.operator_)
        {
            case '+': ans = math::add(task.num1, task.num2); break;
            case '-': ans = math::subtract(task.num1, task.num2); break;
            case 'x': ans = math::multiply(task.num1, task.num2); break;
            case '/': ans = math::divide(task.num1, task.num2); break;
            case '^': ans = math::pow(task.num1, task.num2); break;
            case '!': ans = math::factorial(task.num1); break;
            default: printf("Error: cannot do calculating! Unexpected operator: %c\n", *task.operator_); task.status = 1; return;
        }

        task.result = ans;
        task.status = 0;
        return;
    }

    void printResult(const Task& task)
    {
        if(task.status == 0)
        {
            if( strcmp(task.operator_, "!") == 0 )
            {
                printf("Result: %d! = %d\n", task.num1, task.result);
                return;
            }
            printf("Result: %d %s %d = %d\n", task.num1, task.operator_, task.num2, task.result);
        }
        else
        {
            printf("Error: cannot do calculating! \n");
        }

        return;
    }
}