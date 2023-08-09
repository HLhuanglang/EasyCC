#include "lox.h"
#include "scanner.h"
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <string_view>

void Lox::_run(std::string_view contents) {
    Scanner scanner{contents};
    std::vector<Token> tokens = scanner.scan_tokens();

    // For now, just print the tokens.
    for (const Token &token : tokens) {
        std::cout << token.to_string() << "\n";
    }
}

void Lox::run_prompt() {
    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        _run(line);
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

    _run(contents);
}