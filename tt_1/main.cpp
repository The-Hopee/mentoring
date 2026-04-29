#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int num1 = 0, num2 = 0;
    const char* op = NULL;
    int opt;

    struct option longopts[] = 
    {
        {"num1",   required_argument, NULL, '1'},
        {"num2",   required_argument, NULL, '2'},
        {"op",     required_argument, NULL, 'o'},
        {"help",   no_argument,       NULL, 'h'},
        {NULL,     0,                 NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "h", longopts, NULL)) != -1) // -1 indicates the end of options
    {
        switch (opt)
        {
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
                return 0;
            default:
                fprintf(stderr, "Error: unknown option\n");
                return 1;
        }
    }

    if ((num1 == 0 || num2 == 0 || op == NULL) && strcmp(op, "!") != 0)
    {
        fprintf(stderr, "Error: missing required arguments\n");
        return 1;
    }

    interface::run(num1, num2, op);
    return 0;
}