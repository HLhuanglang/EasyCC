#include "lox.h"
#include <iostream>
#include <string>
#include <string_view>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cout << "Usage: cpplox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        std::string path = argv[1];
        Lox::run_from_file(path);
    } else {
        Lox::run_prompt();
    }
    return 0;
}