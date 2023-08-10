#include "lox.h"
#include "scanner.h"
#include <algorithm>
#include <csignal>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <string_view>

void Lox::_run(std::string_view contents, bool new_line) {
    Scanner scanner{contents};
    std::vector<Token> tokens = scanner.scan_tokens();

    // for循环打印tokens，最后一个token时不打印换行
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it == tokens.end() - 1) {
            if (new_line) {
                std::cout << it->to_string() << "\n";
            } else {
                std::cout << it->to_string();
            }
        } else {
            std::cout << it->to_string() << "\n";
        }
    }
}

void Lox::run_prompt() {
    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        _run(line, true);
    }
}

void Lox::run_from_file(const std::string &path) {
    std::ifstream file{path, std::ios::in | std::ios::binary | std::ios::ate};
    if (!file) {
        std::cerr << "Failed to open file " << path << ": "
                  << std::strerror(errno) << "\n";
        std::exit(74);
    };

    std::string contents;
    contents.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(contents.data(), static_cast<std::streamsize>(contents.size()));

    _run(contents, false);
}