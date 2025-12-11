#pragma once
#include "LgsTokens.h"
#include "errors/LgsErrHandler.h"
#include <filesystem>

namespace fs = std::filesystem;

class LgsLexer {
public:
    fs::path filePath;
    size_t index = 0;
    size_t line = 1;
    size_t column = 1;
    char currentChar = '\0';
    std::string const source;
    LgsErrHandler errHandler;
    std::vector<LgsToken> tokens;

    explicit LgsLexer(const fs::path& filePath, const std::string& src) : filePath(filePath), source(src) {}
    std::vector<LgsToken> tokenize();
    LgsToken nextToken();
    char advance();
    bool match(char expected);
    char peek(size_t offset = 1) const;
    LgsToken scanMatrixDims(const LgsLocation& location, std::string& lexeme);
    LgsToken scanVarOrKeyword(const LgsLocation& location);
    std::string scanDoubleQuotesString();
    std::string scanSingleQuotesString();
    std::string scanMultilineString();
    LgsToken scanNumber(const LgsLocation& location);
    void skipWhitespace();
    void skipLineComment();
    void skipBlockComment();
    void scanEscapeChar(std::string& result);
};