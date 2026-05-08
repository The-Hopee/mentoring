#pragma once
#include <iostream>
#include <stdexcept>
#include "math.h"
#include "logger.h"

namespace interface {

class app
{
private:
    struct Task {
        int num1;
        int num2;
        std::string operator_;
        int result;
        int status;  // 0 - success, 1 - error
    };

    Task task;

    void makeTask(const std::string& json_query);
    void makeCalculate();
    void printResult();
public:
    void run(const std::string& json_query);
};
}  // namespace interface