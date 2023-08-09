#ifndef __EASYCC_LOX_H
#define __EASYCC_LOX_H

#include <string>

class Lox {
 public:
    void run_from_file(const std::string &path);
    void run_prompt();

 private:
    void _run_from_input(const std::string &line);
};

#endif // !__EASYCC_LOX_H
