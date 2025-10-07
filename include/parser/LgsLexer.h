#pragma once
#include "LgsToken.h"
#include "../data/LgsTokens.h"
#include "utils/LgsErrHandler.h"

class LgsLexer {
public:
    size_t fileID;
    size_t line = 1;
    size_t column = 1;
    size_t position = 0;
    char currentChar = '\0';
    std::string const source;
    LgsErrHandler errHandler;
    std::vector<LgsToken> tokens;

    explicit LgsLexer(const size_t fileID, std::string src) : fileID(fileID), source(std::move(src)) {}
    std::vector<LgsToken> tokenize();
    LgsToken nextToken();
    char advance();
    bool match(char expected);
    char peek(size_t offset = 1) const;
    LgsToken scanVarOrKeyword();
    std::string scanString();
    LgsToken scanNumber();
    void skipWhitespace();
    void skipLineComment();
    void skipBlockComment();
    void addLexingError();
};