#ifndef __EASYCC_LOX_H
#define __EASYCC_LOX_H

#include <string>
#include <string_view>

class Lox {
 public:
    static void run_from_file(const std::string &path);
    static void run_prompt();

 private:
    static void _run(std::string_view contents, bool new_line);
};

#endif // !__EASYCC_LOX_H
