#pragma once
#include "data/LgsTokens.h"
#include "utils/LgsErrHandler.h"
#include <filesystem>

namespace fs = std::filesystem;

class LgsLexer {
public:
    size_t fileID;
    fs::path filePath;
    size_t line = 1;
    size_t column = 1;
    size_t position = 0;
    char currentChar = '\0';
    std::string const source;
    LgsErrHandler errHandler;
    std::vector<LgsToken> tokens;

    explicit LgsLexer(const size_t fileID, const fs::path& filePath, std::string src) : fileID(fileID), filePath(filePath), source(std::move(src)) {}
    std::vector<LgsToken> tokenize();
    LgsToken nextToken();
    char advance();
    bool match(char expected);
    char peek(size_t offset = 1) const;
    LgsToken scanVarOrKeyword(LgsLocation& location);
    std::string scanDoubleQuotesString();
    std::string scanSingleQuotesString();
    std::string scanMultilineString();
    LgsToken scanNumber(LgsLocation& location);
    void skipWhitespace();
    void skipLineComment();
    void skipBlockComment();
};