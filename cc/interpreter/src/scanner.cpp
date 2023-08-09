#include "scanner.h"
#include "error.h"
#include "toekn.h"
#include <any>
#include <vector>

const std::map<std::string, token_type_e> Scanner::g_s_keywords =
    {
        {"and", token_type_e::AND},
        {"class", token_type_e::CLASS},
        {"else", token_type_e::ELSE},
        {"false", token_type_e::FALSE},
        {"for", token_type_e::FOR},
        {"fun", token_type_e::FUN},
        {"if", token_type_e::IF},
        {"nil", token_type_e::NIL},
        {"or", token_type_e::OR},
        {"print", token_type_e::PRINT},
        {"return", token_type_e::RETURN},
        {"super", token_type_e::SUPER},
        {"this", token_type_e::THIS},
        {"true", token_type_e::TRUE},
        {"var", token_type_e::VAR},
        {"while", token_type_e::WHILE},
};

std::vector<Token> Scanner::scan_tokens() {
    while (!_is_at_end()) {
        m_start = m_curr;
        _scan();
    }
    return m_tokens;
}

char Scanner::_advance() {
    return m_source[m_curr++];
}

void Scanner::_add_token(token_type_e type, std::any iteral) {
    std::string text{m_source.substr(m_start, m_curr - m_start)};
    m_tokens.emplace_back(type, std::move(text), std::move(iteral),
                          m_line);
}

void Scanner::_add_token(token_type_e type) {
    _add_token(type, nullptr);
}

bool Scanner::_is_at_end() {
    return m_curr >= m_source.length();
}

char Scanner::_peek() {
    if (_is_at_end()) {
        return '\0';
    }
    return m_source[m_curr];
}

char Scanner::_peek_next() {
    if (m_curr + 1 >= m_source.length()) {
        return '\0';
    }
    return m_source[m_curr + 1];
}

bool Scanner::_match(char expected) {
    if (_is_at_end()) {
        return false;
    }
    if (m_source[m_curr] != expected) {
        return false;
    }
    ++m_curr;
    return true;
}

void Scanner::_string() {
    while (_peek() != '"' && !_is_at_end()) {
        if (_peek() == '\n') {
            ++m_line;
        }
        _advance();
    }

    if (_is_at_end()) {
        error(m_line, "Unterminated string.");
        return;
    }

    // The closing ".
    _advance();

    // Trim the surrounding quotes.
    std::string value{m_source.substr(m_start + 1, m_curr - 2 - m_start)};
    _add_token(STRING, value);
}

bool Scanner::_is_digit(char c) {
    return c >= '0' && c <= '9';
}

void Scanner::_number() {
    while (_is_digit(_peek())) {
        _advance();
    }

    // Look for a fractional part.
    if (_peek() == '.' && _is_digit(_peek_next())) {
        // Consume the "."
        _advance();

        while (_is_digit(_peek())) {
            _advance();
        }
    }

    _add_token(NUMBER, std::stod(std::string{m_source.substr(m_start, m_curr - m_start)}));
}

bool Scanner::_is_alph(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::_is_alph_numeric(char c) {
    return _is_alph(c) || _is_digit(c);
}

void Scanner::_identifier() {
    while (_is_alph_numeric(_peek())) {
        _advance();
    }

    std::string text = std::string{m_source.substr(m_start, m_curr - m_start)};

    token_type_e type;
    auto match = g_s_keywords.find(text);
    if (match == g_s_keywords.end()) {
        type = IDENTIFIER;
    } else {
        type = match->second;
    }

    _add_token(type);
}

void Scanner::_scan() {
    char c = _advance();
    switch (c) {
        case ' ':
        case '\t':
        case '\r':
            break;
        case '\n':
            m_line++;
            break;
        case '(':
            _add_token(token_type_e::LEFT_PAREN);
            break;
        case ')':
            _add_token(token_type_e::RIGHT_PAREN);
            break;
        case '{':
            _add_token(token_type_e::LEFT_BRACE);
            break;
        case '}':
            _add_token(token_type_e::RIGHT_BRACE);
            break;
        case ',':
            _add_token(token_type_e::COMMA);
            break;
        case '.':
            _add_token(token_type_e::DOT);
            break;
        case '-':
            _add_token(token_type_e::MINUS);
            break;
        case '+':
            _add_token(token_type_e::PLUS);
            break;
        case ';':
            _add_token(token_type_e::SEMICOLON);
            break;
        case '*':
            _add_token(token_type_e::STAR);
            break;
        case '!':
            _add_token(_match('=') ? token_type_e::BANG_EQUAL : token_type_e::BANG);
            break;
        case '=':
            _add_token(_match('=') ? token_type_e::EQUAL_EQUAL : token_type_e::EQUAL);
            break;
        case '<':
            _add_token(_match('=') ? token_type_e::LESS_EQUAL : token_type_e::LESS);
            break;
        case '>':
            _add_token(_match('=') ? token_type_e::GREATER_EQUAL : token_type_e::GREATER);
            break;
        case '/':
            if (_match('/')) {
                while (_peek() != '\n' && !_is_at_end()) {
                    _advance();
                }
            } else {
                _add_token(token_type_e::SLASH);
            }
            break;
        case '"':
            _string();
            break;
        default:
            if (_is_digit(c)) {
                _number();
            } else if (_is_alph(c)) {
                _identifier();
            } else {
                error(m_line, "Unexpected character.");
            }
            break;
    }
}