#pragma once
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int num1;
    int num2;
    const char* operator_;
    int result;
    int status;  // 0 - success, 1 - error
};

namespace interface {
void run(int argc, char** argv);

void makeTask(Task&, int, char**);
void makeCalculate(Task&);
void printResult(const Task&);
}  // namespace interface