#include "parser/LgsLexer.h"
#include <cassert>

std::vector<LgsToken> LgsLexer::tokenize() {
    if (source.empty()) return {};
    currentChar = source[0];
    while (true) {
        auto token = nextToken();
        tokens.push_back(token);
        if (token.type == T_EOF) break;
    }
    return tokens;
}

LgsToken LgsLexer::nextToken() {
    skipWhitespace();
    LgsLocation location{fileID, position, line, column};
    if (currentChar == '\0') return {T_EOF, "", location};

    // Comments
    if (currentChar == '/' && peek() == '/') {
        skipLineComment();
        return nextToken();
    }
    if (currentChar == '/' && peek() == '/' && peek(2) == '/') {
        skipBlockComment();
        return nextToken();
    }

    // Tag
    if (currentChar == '@') {
        advance();
        std::string lexeme = "@";
        while (std::isalnum(currentChar) || currentChar == '_') {
            lexeme += advance();
        }
        return {T_TAG, lexeme, location};
    }

    // Dot, range or spread
    if (currentChar == '.') {
        advance();
        if (currentChar == '.') {
            advance();
            if (currentChar == '.') {
                advance();
                return {T_TRIPLE_DOT, "...", location};
            }
            return {T_DOUBLE_DOT, "..", location};
        }
        if (std::isdigit(currentChar)) return scanNumber(location);
        return {T_DOT, ".", location};
    }

    // Number
    if (std::isdigit(currentChar)) {
        return scanNumber(location);
    }
    if (currentChar == '-' && std::isdigit(peek())) {
        return scanNumber(location);
    }

    // Var or keyword
    if (currentChar == '$' || std::isalpha(currentChar)) {
        return scanVarOrKeyword(location);
    }

    // String
    if (currentChar == '"' && peek() == '"') {
        return {T_STRING, scanMultilineString(), location};
    }
    if (currentChar == '"') {
        return {T_STRING, scanDoubleQuotesString(), location};
    }
    if (currentChar == '\'') {
        return {T_STRING, scanSingleQuotesString(), location};
    }

    switch (currentChar) {
    case '(': advance(); return {T_LPAREN, "(", location};
    case ')': advance(); return {T_RPAREN, ")", location};
    case '{': advance(); return {T_LBRACE, "{", location};
    case '}': advance(); return {T_RBRACE, "}", location};
    case '[': advance(); return {T_LBRACK, "[", location};
    case ']': advance(); return {T_RBRACK, "]", location};
    case ',': advance(); return {T_COMMA, ",", location};
    case '?': advance(); return {T_QUEST_MARK, "?", location};
    case '=':
        advance();
        if (match('=')) return {T_DOUBLE_EQUAL, "==", location};
        if (match('>')) return {T_DARROW, "=>", location};
        return {T_EQUAL, "=", location};
    case '!':
        advance();
        if (match('=')) return {T_NOT_EQUAL, "!=", location};
        return {T_EXCLA_MARK, "!", location};
    case '<':
        advance();
        if (match('<')) {
            if (match('=')) return {T_EQUAL_DOUBLE_RANGLE, "<<=", location};
            return {T_DOUBLE_RANGLE, "<<", location};
        }
        if (currentChar == '=') return {T_LE, "<=", location};
        return {T_LANGLE, "<", location};
    case '>':
        advance();
        if (match('>')) {
            if (match('=')) return {T_EQUAL_DOUBLE_LANGLE, ">>=", location};
            return {T_DOUBLE_LANGLE, ">>", location};
        }
        if (currentChar == '=') return {T_GE, ">=", location};
        return {T_RANGLE, ">", location};
    case ':':
        advance();
        if (match('=')) return {T_WALRUS, ":=", location};
        return {T_COLON, ":", location};
    case '+':
        advance();
        if (match('+')) return {T_INC, "++", location};
        if (match('=')) return {T_EQUAL_PLUS, "+=", location};
        return {T_PLUS, "+", location};
    case '-':
        advance();
        if (match('-')) return {T_DEC, "--", location};
        if (match('>')) return {T_ARROW, "->", location};
        if (match('=')) return {T_EQUAL_MINUS, "-=", location};
        return {T_MINUS, "-", location};
    case '*':
        advance();
        if (match('=')) return {T_EQUAL_STAR, "*=", location};
        return {T_STAR, "*", location};
    case '_':
        advance();
        if (match('/')) return {T_SLIDER, "_/", location};
        if (std::isalpha(peek(-1))) {
            position--;
            column--;
            return scanVarOrKeyword(location);
        }
        return {T_IDENTIFIER, "_", location};
    case '/':
        advance();
        if (match('=')) return {T_EQUAL_SLASH, "/=", location};
        return {T_SLASH, "/", location};
    case '%': {
        advance();
        if (match('=')) return {T_EQUAL_PERCENT, "%=", location};
        return {T_PERCENT, "%", location};
    }
    case '&':
        advance();
        if (match('=')) return {T_EQUAL_AMPERSAND, "&=", location};
        return {T_AMPERSAND, "&", location};
    case '|':
        advance();
        if (match('=')) return {T_EQUAL_PIPE, "|=", location};
        return {T_PIPE, "|", location};
    case '^':
        advance();
        if (match('=')) return {T_EQUAL_CARET, "^=", location};
        return {T_CARET, "^", location};
    default:
        errHandler.addError(E10088, &location, filePath, {});
        return {T_EOF, "", location};
    }
}

char LgsLexer::advance() {
    if (position >= source.length()) {
        currentChar = '\0';
        return currentChar;
    }
    currentChar = source[++position];
    if (currentChar == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return currentChar;
}

bool LgsLexer::match(const char expected) {
    if (currentChar == expected) {
        advance();
        return true;
    }
    return false;
}

char LgsLexer::peek(const size_t offset) const {
    if (position + offset >= source.length()) return '\0';
    return source[position + offset];
}

LgsToken LgsLexer::scanVarOrKeyword(LgsLocation& location) {
    std::string lexeme;
    auto isDollared = false;
    if (currentChar == '$') {
        lexeme = "$";
        isDollared = true;
        advance();
    }

    while (std::isalnum(currentChar) || currentChar == '_') {
        lexeme += currentChar;
        advance();
        location.columnStart++;
        if (std::isspace(currentChar)) break;
    }

    if (isDollared) return {T_DOLLAR_IDENTIFIER, lexeme, location};
    if (lexeme == "for") {
        if (!match('.')) return {T_FOR, lexeme, location};
        std::string metaVar;
        while (std::isalnum(currentChar)) {
            metaVar += currentChar;
            advance();
            location.columnStart++;
            if (std::isspace(currentChar)) break;
        }
        const auto combined = lexeme + '.' + metaVar;
        if (metaVar == "i") return {T_FOR_I, combined, location};
        if (metaVar == "isFirst") return {T_FOR_IS_FIRST, combined, location};
        if (metaVar == "isLast") return {T_FOR_IS_LAST, combined, location};
        if (metaVar == "ever") return {T_FOR_EVER, combined, location};
        errHandler.addError(E10088, &location, filePath, {});
        return {T_EOF, "", location};
    }

    auto const it = LGS_KEYWORDS.find(lexeme);
    if (it != LGS_KEYWORDS.end()) {
        return {it->second, lexeme, location};
    }
    return {T_IDENTIFIER, lexeme, location};
}

std::string LgsLexer::scanDoubleQuotesString() {
    advance();
    std::string result;
    while (currentChar != '"' && currentChar != '\0') {
        result += currentChar;
        advance();
    }
    if (currentChar == '"') advance();
    return result;
}

std::string LgsLexer::scanSingleQuotesString() {
    advance();
    std::string result;
    while (currentChar != '\'' && currentChar != '\0') {
        result += currentChar;
        advance();
    }
    if (currentChar == '\'') advance();
    return result;
}

std::string LgsLexer::scanMultilineString() {
    advance();
    advance();
    std::string result;
    while (currentChar != '\0') {
        if (currentChar == '"' && peek() == '"') {
            advance();
            advance();
            break;
        }
        result += currentChar;
        advance();
    }
    return result;
}

LgsToken LgsLexer::scanNumber(LgsLocation& location) {
    std::string lexeme;
    // Minus
    if (currentChar == '-') {
        lexeme += currentChar;
        advance();
        location.columnStart++;
    }
    // Hexadecimal
    if (currentChar == '0' && (peek() == 'x' || peek() == 'X')) {
        lexeme += currentChar;
        advance();
        lexeme += currentChar;
        advance();
        location.columnStart += 2;
        while (std::isxdigit(currentChar) || currentChar == '_') {
            lexeme += currentChar;
            advance();
            location.columnStart++;
        }
        return {T_HEX, lexeme, location};
    }
    // Int
    while (std::isdigit(currentChar) || currentChar == '_') {
        lexeme += currentChar;
        advance();
        location.columnStart++;
    }
    // Float
    if (currentChar == '.' && peek() != '.') {
        lexeme += currentChar;
        advance();
        location.columnStart++;
        while (std::isdigit(currentChar)) {
            lexeme += currentChar;
            advance();
            location.columnStart++;
        }
        return {T_FLOAT, lexeme, location};
    }
    // Long
    if (currentChar == 'L') {
        lexeme += currentChar;
        advance();
        location.columnStart++;
        return {T_LONG, lexeme, location};
    }
    return {T_INT, lexeme, location};
}

void LgsLexer::skipWhitespace() {
    while (std::isspace(currentChar)) {
        advance();
    }
}

void LgsLexer::skipLineComment() {
    while (currentChar != '\n' && currentChar != '\0') {
        advance();
    }
}

void LgsLexer::skipBlockComment() {
    advance();
    advance();
    advance();
    while (true) {
        if (currentChar == '\0') break;
        if (currentChar == '/' && peek() == '/' && peek(2) == '/') {
            advance();
            advance();
            advance();
            break;
        }
        advance();
    }
}