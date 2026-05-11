#include "interface.h"

int main(int argc, char **argv) { // ./calculator '{"num1": 5, "num2": 3, "op": "x"}'
    std::string json_query = argc < 2 ? "" : argv[1];
    interface::app application;
    application.run(json_query);
    return 0;
}