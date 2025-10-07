#pragma once
#include "LgsTokens.h"

#include <string>
#include <vector>

struct Token {
    TokenType type;
    std::string lexeme;
    size_t line;
    size_t column;
};

class Lexer {
public:
    std::string const source;
    size_t position = 0;
    size_t line = 1;
    size_t column = 1;

    explicit Lexer(std::string src) : source(std::move(src)) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (true) {
            auto token = nextToken();
            tokens.push_back(token);
            if (token.type == TokenType::END_OF_FILE) break;
        }
        return tokens;
    }

    char advance() {
        if (position >= source.length()) return '\0';
        auto const ch = source[position++];
        if (ch == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        return ch;
    }

    Token nextToken() {
        skipWhitespace();
        if (current() == '\0') return {TokenType::END_OF_FILE, "", line, column};
        auto const startLine = line;
        auto const startColumn = column;
        auto const ch = current();
        if (ch == '/' && peek() == '/' && peek(2) != '/') {
            skipLineComment();
            return nextToken();
        }
        if (ch == '/' && peek() == '/' && peek(2) == '/') {
            skipBlockComment();
            return nextToken();
        }
        if (ch == '"') {
            auto const str = scanString();
            return {TokenType::STRING, "\"" + str + "\"", startLine, startColumn};
        }
        if (ch == '@') {
            advance();
            std::string lexeme = "@";
            while (std::isalnum(current()) || current() == '_') {
                lexeme += advance();
            }
            return {TokenType::TAG, lexeme, startLine, startColumn};
        }
        if (ch == '.') {
            advance();
            if (current() == 'j' && peek() == 's' && peek(2) == 'o' && peek(3) == 'n') {
                std::string lexeme = ".json";
                advance();
                advance();
                advance();
                advance();
                return {TokenType::JSON, lexeme, startLine, startColumn};
            }
            if (current() == '.') {
                advance();
                if (current() == '.') {
                    advance();
                    return {TokenType::TRIPLE_DOT, "...", startLine, startColumn};
                }
                return {TokenType::DOUBLE_DOT, "..", startLine, startColumn};
            }
            return {TokenType::DOT, ".", startLine, startColumn};
        }
        if (std::isdigit(ch)) {
            return scanNumber();
        }
        if (ch == '-' && std::isdigit(peek())) {
            return scanNumber();
        }
        if (std::isalpha(ch)) {
            return scanIdentifierOrKeyword();
        }
        advance();
        switch (ch) {
            case '(': return {TokenType::LPAREN, "(", startLine, startColumn};
            case ')': return {TokenType::RPAREN, ")", startLine, startColumn};
            case '{': return {TokenType::LBRACE, "{", startLine, startColumn};
            case '}': return {TokenType::RBRACE, "}", startLine, startColumn};
            case '[': return {TokenType::LBRACK, "[", startLine, startColumn};
            case ']': return {TokenType::RBRACK, "]", startLine, startColumn};
            case ',': return {TokenType::COMMA, ",", startLine, startColumn};
            case '#': return {TokenType::HASH, "#", startLine, startColumn};
            case '?': return {TokenType::QUEST_MARK, "?", startLine, startColumn};
            case '$': return {TokenType::DOLLAR, "$", startLine, startColumn};
            case '=':
                if (match('=')) return {TokenType::DOUBLE_EQUAL, "==", startLine, startColumn};
                return {TokenType::EQUAL, "=", startLine, startColumn};
            case '!':
                if (match('=')) return {TokenType::NOT_EQUAL, "!=", startLine, startColumn};
                return {TokenType::EXCLA_MARK, "!", startLine, startColumn};
            case '<':
                if (match('<')) {
                    if (match('=')) return {TokenType::EQUAL_DOUBLE_RANGLE, "<<=", startLine, startColumn};
                    return {TokenType::DOUBLE_RANGLE, "<<", startLine, startColumn};
                }
                if (match('=')) return {TokenType::LE, "<=", startLine, startColumn};
                return {TokenType::LANGLE, "<", startLine, startColumn};
            case '>':
                if (match('>')) {
                    if (match('=')) return {TokenType::EQUAL_DOUBLE_LANGLE, ">>=", startLine, startColumn};
                    return {TokenType::DOUBLE_LANGLE, ">>", startLine, startColumn};
                }
                if (match('=')) return {TokenType::GE, ">=", startLine, startColumn};
                return {TokenType::RANGLE, ">", startLine, startColumn};
            case ':':
                if (match('=')) return {TokenType::WALRUS, ":=", startLine, startColumn};
                return {TokenType::COLON, ":", startLine, startColumn};
            case '+':
                if (match('+')) return {TokenType::INC, "++", startLine, startColumn};
                if (match('=')) return {TokenType::EQUAL_PLUS, "+=", startLine, startColumn};
                return {TokenType::PLUS, "+", startLine, startColumn};
            case '-':
                if (match('-')) return {TokenType::DEC, "--", startLine, startColumn};
                if (match('>')) return {TokenType::ARROW, "->", startLine, startColumn};
                if (match('=')) return {TokenType::EQUAL_MINUS, "-=", startLine, startColumn};
                return {TokenType::MINUS, "-", startLine, startColumn};
            case '*':
                if (match('=')) return {TokenType::EQUAL_STAR, "*=", startLine, startColumn};
                return {TokenType::STAR, "*", startLine, startColumn};
            case '_':
                if (match('/')) return {TokenType::SLIDER, "_/", startLine, startColumn};
                if (std::isalpha(peek(-1))) {
                    position--;
                    column--;
                    return scanIdentifierOrKeyword();
                }
                return {TokenType::IDENTIFIER, "_", startLine, startColumn};
            case '/':
                if (match('=')) return {TokenType::EQUAL_SLASH, "/=", startLine, startColumn};
                return {TokenType::SLASH, "/", startLine, startColumn};
            case '%':
                if (match('=')) return {TokenType::EQUAL_PERCENT, "%=", startLine, startColumn};
                return {TokenType::PERCENT, "%", startLine, startColumn};
            case '&':
                if (match('=')) return {TokenType::EQUAL_AMPERSAND, "&=", startLine, startColumn};
                return {TokenType::AMPERSAND, "&", startLine, startColumn};
            case '|':
                if (match('=')) return {TokenType::EQUAL_PIPE, "|=", startLine, startColumn};
                return {TokenType::PIPE, "|", startLine, startColumn};
            case '^':
                if (match('=')) return {TokenType::EQUAL_CARET, "^=", startLine, startColumn};
                return {TokenType::CARET, "^", startLine, startColumn};
            default:
                assert(0);
        }
    }

    Token scanIdentifierOrKeyword() {
        auto const startLine = line;
        auto const startColumn = column;
        std::string lexeme;
        while (std::isalnum(current()) || current() == '_') {
            lexeme += advance();
        }
        if (lexeme == "object") return {TokenType::OBJECT, lexeme, startLine, startColumn};
        if (lexeme == "single") return {TokenType::SINGLETON, lexeme, startLine, startColumn};
        if (lexeme == "self") return {TokenType::SELF_INSTANCE, lexeme, startLine, startColumn};
        if (lexeme == "Self") return {TokenType::SELF_CLASS, lexeme, startLine, startColumn};
        if (lexeme == "interface") return {TokenType::INTERFACE, lexeme, startLine, startColumn};
        if (lexeme == "extern") return {TokenType::EXTERN, lexeme, startLine, startColumn};
        if (lexeme == "pub") return {TokenType::VISIBILITY, lexeme, startLine, startColumn};
        if (lexeme == "implements") return {TokenType::IMPLEMENTS, lexeme, startLine, startColumn};
        if (lexeme == "const") return {TokenType::CONST, lexeme, startLine, startColumn};
        if (lexeme == "enum") return {TokenType::ENUM, lexeme, startLine, startColumn};
        if (lexeme == "go") return {TokenType::GO, lexeme, startLine, startColumn};
        if (lexeme == "defer") return {TokenType::DEFER, lexeme, startLine, startColumn};
        if (lexeme == "io") return {TokenType::IO, lexeme, startLine, startColumn};
        if (lexeme == "owner") return {TokenType::OWNER, lexeme, startLine, startColumn};
        if (lexeme == "and") return {TokenType::AND, lexeme, startLine, startColumn};
        if (lexeme == "or") return {TokenType::OR, lexeme, startLine, startColumn};
        if (lexeme == "not") return {TokenType::NOT, lexeme, startLine, startColumn};
        if (lexeme == "in") return {TokenType::IN, lexeme, startLine, startColumn};
        if (lexeme == "if") return {TokenType::IF, lexeme, startLine, startColumn};
        if (lexeme == "while") return {TokenType::WHILE, lexeme, startLine, startColumn};
        if (lexeme == "else") return {TokenType::ELSE, lexeme, startLine, startColumn};
        if (lexeme == "break") return {TokenType::BREAK, lexeme, startLine, startColumn};
        if (lexeme == "continue") return {TokenType::CONTINUE, lexeme, startLine, startColumn};
        if (lexeme == "return") return {TokenType::RETURN, lexeme, startLine, startColumn};
        if (lexeme == "for.i") return {TokenType::FOR, lexeme, startLine, startColumn};
        if (lexeme == "for.ever") return {TokenType::FOR, lexeme, startLine, startColumn};
        if (lexeme == "for.isFirst") return {TokenType::FOR, lexeme, startLine, startColumn};
        if (lexeme == "for.isLast") return {TokenType::FOR, lexeme, startLine, startColumn};
        if (lexeme == "for") return {TokenType::FOR, lexeme, startLine, startColumn};
        if (lexeme == "vec2") return {TokenType::VEC2, lexeme, startLine, startColumn};
        if (lexeme == "vec3") return {TokenType::VEC3, lexeme, startLine, startColumn};
        if (lexeme == "vec4") return {TokenType::VEC4, lexeme, startLine, startColumn};
        if (lexeme == "true" || lexeme == "false") return {TokenType::BOOL, lexeme, startLine, startColumn};
        if (lexeme == "null") return {TokenType::NULL_TOKEN, lexeme, startLine, startColumn};
        return {TokenType::IDENTIFIER, lexeme, startLine, startColumn};
    }

    std::string scanString() {
        std::string result;
        advance();
        while (current() != '"' && current() != '\0') {
            if (current() == '\\') {
                advance();
                if (current() != '\0') {
                    result += current();
                    advance();
                }
            } else {
                result += current();
                advance();
            }
        }
        if (current() == '"') advance();
        return result;
    }

    Token scanNumber() {
        auto const startLine = line;
        auto const startColumn = column;
        std::string lexeme;
        auto const isNegative = current() == '-';
        if (isNegative) {
            lexeme += advance();
        }
        auto hasDigit = false;
        while (std::isdigit(current()) || current() == '_') {
            if (std::isdigit(current())) hasDigit = true;
            lexeme += advance();
        }
        if (current() == '.' && std::isdigit(peek())) {
            lexeme += advance();
            while (std::isdigit(current())) {
                lexeme += advance();
            }
            return {TokenType::FLOAT, lexeme, startLine, startColumn};
        }
        if (current() == 'L') {
            lexeme += advance();
            return {TokenType::LONG, lexeme, startLine, startColumn};
        }
        return {TokenType::INTEGER, lexeme, startLine, startColumn};
    }

    char current() const {
        if (position >= source.length()) return '\0';
        return source[position];
    }

    char peek(const size_t offset = 1) const {
        if (position + offset >= source.length()) return '\0';
        return source[position + offset];
    }

    bool match(const char expected) {
        if (current() == expected) {
            advance();
            return true;
        }
        return false;
    }

    void skipWhitespace() {
        while (std::isspace(current())) {
            advance();
        }
    }

    void skipLineComment() {
        while (current() != '\n' && current() != '\0') {
            advance();
        }
    }

    void skipBlockComment() {
        advance();
        advance();
        advance();
        while (true) {
            if (current() == '\0') break;
            if (current() == '/' && peek() == '/' && peek(2) == '/') {
                advance();
                advance();
                advance();
                break;
            }
            advance();
        }
    }
};