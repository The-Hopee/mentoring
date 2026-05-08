#include "interface.h"

int main(int argc, char **argv) {
    std::string json_query = argc < 2 ? "" : argv[1];
    interface::app application;
    application.run(json_query);
    return 0;
}