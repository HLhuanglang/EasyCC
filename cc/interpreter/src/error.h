#ifndef __EASYCC_ERROR_H
#define __EASYCC_ERROR_H

#include <iostream>
#include <string_view>

static void report(int line, std::string_view where, std::string_view msg) {
    std::cerr << "[line " << line << "] Error" << where << ": " << msg << std::endl;
}

inline void error(int line, std::string_view msg) {
    report(line, "", msg);
}

#endif // !__EASYCC_ERROR_H
