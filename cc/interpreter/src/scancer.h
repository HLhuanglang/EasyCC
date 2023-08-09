#ifndef __EASYCC_SCANCER_H
#define __EASYCC_SCANCER_H

#include <string_view>

class Scancer {
 public:
    Scancer(std::string_view source) : m_source(source) {}

 public:
    void scan();
    void readline();
    void addvance();

 private:
    std::string_view m_source;
};

#endif // !__EASYCC_SCANCER_H
