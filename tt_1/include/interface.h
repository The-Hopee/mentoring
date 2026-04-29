#pragma once
#include <stdio.h>

struct Task
{
    int num1;
    int num2;
    const char* operator_;
    int result;
    int status; // 0 - success, 1 - error
};

namespace interface
{
    void run(int num1, int num2, const char* operator_);

    void makeTask(Task);
    void makeCalculate(Task&);
    void printResult(const Task&);
}