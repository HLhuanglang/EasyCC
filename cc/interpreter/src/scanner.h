#ifndef __EASYCC_SCANNER_H
#define __EASYCC_SCANNER_H

#include "token.h"
#include <map>
#include <string_view>
#include <vector>

class Scanner {
 public:
    Scanner(std::string_view source) : m_source(source) {}

 public:
    std::vector<Token> scan_tokens();

 private:
    char _advance();           //获取当前字符并向前移动1位
    char _advance_n(int step); //获取当前字符并向前移动step位
    void _scan();
    void _add_token(token_type_e type);
    void _add_token(token_type_e type, std::any literal);
    bool _is_at_end();
    char _peek();
    char _peek_next();
    bool _match(char expected);
    void _string();
    static bool _is_digit(char c);
    void _number();
    static bool _is_alph(char c);
    static bool _is_alph_numeric(char c);
    void _identifier();
    bool _is_right_block_comment(); //右块注释 */

 private:
    std::string_view m_source; //存储所有源码
    std::vector<Token> m_tokens;
    int m_start = 0;
    int m_curr = 0;
    int m_line = 0;
    const static std::map<std::string, token_type_e> g_s_keywords;
};

#endif // !__EASYCC_SCANNER_H
