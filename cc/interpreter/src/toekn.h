#ifndef __EASYCC_TOEKN_H
#define __EASYCC_TOEKN_H

#include <string>
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

#endif // !__EASYCC_TOEKN_H
