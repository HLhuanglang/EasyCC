#include "lox.h"
#include <iostream>
#include <string>
#include <string_view>

int main(int argc, char *argv[]) {
    Lox cpplox;
    if (argc > 2) {
        std::cout << "Usage: cpplox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        std::string path = argv[1];
        cpplox.run_from_file(path);
    } else {
        cpplox.run_prompt();
    }
    return 0;
}