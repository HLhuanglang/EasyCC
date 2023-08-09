#include "lox.h"
#include "scancer.h"
#include <iostream>
#include <string_view>

void Lox::_run_from_input(const std::string &line) {
    // todo
}

void Lox::run_prompt() {
    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            _run_from_input(line);
        }
    }
}

void Lox::run_from_file(const std::string &path) {
    // todo
}