#include "interface.h"

namespace interface {
void run(int argc, char** argv) {
    Task task{};

    makeTask(task, argc, argv);
    makeCalculate(task);
    printResult(task);

    return;
}

void makeTask(Task& task, int argc, char** argv) {
    int num1 = 0, num2 = 0;
    const char* op = NULL;
    int opt;

    struct option longopts[] = {{"num1", required_argument, NULL, '1'},
                                {"num2", required_argument, NULL, '2'},
                                {"op", required_argument, NULL, 'o'},
                                {"help", no_argument, NULL, 'h'},
                                {NULL, 0, NULL, 0}};

    while ((opt = getopt_long(argc, argv, "h", longopts, NULL)) !=
           -1)  // -1 indicates the end of options
    {
        switch (opt) {
            case '1':
                num1 = strtol(optarg, NULL, 10);
                break;
            case '2':
                num2 = strtol(optarg, NULL, 10);
                break;
            case 'o':
                op = optarg;
                break;
            case 'h':
                printf("Usage: %s --num1 <n1> --num2 <n2> --op <operator>\n", argv[0]);
                printf("Example: %s --num1 5 --num2 3 --op x\n", argv[0]);
                return;
            default:
                fprintf(stderr, "Error: unknown option\n");
                return;
        }
    }

    if (op == NULL) {
        fprintf(stderr, "Error: missing required arguments\n");
        task.status = 1;
        return;
    }

    if (strcmp(op, "!") == 0) {
        if (num1 == 0) {
            fprintf(stderr, "Error: missing required argument for factorial\n");
            task.status = 1;
            return;
        }
        printf("Task created: %d %s\n", num1, op);
        task.num1 = num1;
        task.operator_ = op;
        return;
    }

    if (num1 == 0 || num2 == 0) {
        fprintf(stderr, "Error: missing required arguments\n");
        task.status = 1;
        return;
    }

    task.num1 = num1;
    task.num2 = num2;
    task.operator_ = op;

    printf("Task created: %d %s %d\n", num1, op, num2);
    return;
}

void makeCalculate(Task& task) {
    if (task.status != 0 || task.operator_ == NULL) {
        return;
    }

    int ans = 0;

    switch (*task.operator_) {
        case '+':
            ans = math::add(task.num1, task.num2);
            break;
        case '-':
            ans = math::subtract(task.num1, task.num2);
            break;
        case 'x':
            ans = math::multiply(task.num1, task.num2);
            break;
        case '/':
            ans = math::divide(task.num1, task.num2);
            break;
        case '^':
            ans = math::pow(task.num1, task.num2);
            break;
        case '!':
            ans = math::factorial(task.num1);
            break;
        default:
            printf("Error: cannot do calculating! Unexpected operator: %c\n", *task.operator_);
            task.status = 1;
            return;
    }

    task.result = ans;
    task.status = 0;
    return;
}

void printResult(const Task& task) {
    if (task.operator_ == NULL) {
        return;
    }

    if (task.status == 0) {
        if (strcmp(task.operator_, "!") == 0) {
            printf("Result: %d! = %d\n", task.num1, task.result);
            return;
        }
        printf("Result: %d %s %d = %d\n", task.num1, task.operator_, task.num2, task.result);
    } else {
        printf("Error: cannot do calculating! \n");
    }

    return;
}
}  // namespace interface