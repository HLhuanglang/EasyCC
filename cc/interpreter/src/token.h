#ifndef __EASYCC_TOEKN_H
#define __EASYCC_TOEKN_H

#include <any>
#include <string>
#include <utility>
#include <vector>

enum token_type_e {
    // Single-character tokens.
    LEFT_PAREN,    // (
    RIGHT_PAREN,   // )
    LEFT_BRACE,    // {
    RIGHT_BRACE,   // }
    COMMA,         // ,
    DOT,           // .
    MINUS,         // -
    PLUS,          // +
    SEMICOLON,     // ;
    SLASH,         // /
    STAR,          // *
    BANG,          // !
    BANG_EQUAL,    // !=
    EQUAL,         // =
    EQUAL_EQUAL,   // ==
    GREATER,       // >
    GREATER_EQUAL, // >=
    LESS,          // <
    LESS_EQUAL,    // <=

    // Literals.
    IDENTIFIER, // Identifiers.
    STRING,     // String literals.
    NUMBER,     // Number literals.

    // Keywords.
    AND,    // and
    CLASS,  // class
    ELSE,   // else
    FALSE,  // false
    FUN,    // fun
    FOR,    // for
    IF,     // if
    NIL,    // nil
    OR,     // or
    PRINT,  // print
    RETURN, // return
    SUPER,  // super
    THIS,   // this
    TRUE,   // true
    VAR,    // var
    WHILE,  // while

    END_OF_FILE
};

inline std::string to_string(token_type_e type) {
    static const std::vector<std::string> s_token_strings = {
        "LEFT_PAREN",
        "RIGHT_PAREN",
        "LEFT_BRACE",
        "RIGHT_BRACE",
        "COMMA",
        "DOT",
        "MINUS",
        "PLUS",
        "SEMICOLON",
        "SLASH",
        "STAR",
        "BANG",
        "BANG_EQUAL",
        "EQUAL",
        "EQUAL_EQUAL",
        "GREATER",
        "GREATER_EQUAL",
        "LESS",
        "LESS_EQUAL",
        "IDENTIFIER",
        "STRING",
        "NUMBER",
        "AND",
        "CLASS",
        "ELSE",
        "FALSE",
        "FUN",
        "FOR",
        "IF",
        "NIL",
        "OR",
        "PRINT",
        "RETURN",
        "SUPER",
        "THIS",
        "TRUE",
        "VAR",
        "WHILE",
        "END_OF_FILE"};

    return s_token_strings[static_cast<int>(type)];
}

class Token {
 public:
    Token(token_type_e type, std::string lexeme, std::any literal, int line)
        : m_type(type), m_lexeme(std::move(lexeme)), m_literal(std::move(literal)), m_line(line) {}

 public:
    [[nodiscard]] std::string to_string() const {
        std::string literal_text;
        switch (m_type) {
            case (IDENTIFIER):
                literal_text = m_lexeme;
                break;
            case (STRING):
                literal_text = std::any_cast<std::string>(m_literal);
                break;
            case (NUMBER):
                literal_text = std::to_string(std::any_cast<double>(m_literal));
                break;
            case (TRUE):
                literal_text = "true";
                break;
            case (FALSE):
                literal_text = "false";
                break;
            default:
                literal_text = "nil";
        }
        return ::to_string(m_type) + " " + m_lexeme + " " + literal_text;
    }

 public:
    const token_type_e m_type;
    const std::string m_lexeme;
    const int m_line;
    const std::any m_literal;
};

#endif // !__EASYCC_TOEKN_H
