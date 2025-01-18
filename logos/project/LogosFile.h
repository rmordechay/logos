#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include "LogosLexer.h"
#include "LogosParser.h"

#include <filesystem>
#include <string>

class LogosFile {
public:
    std::string code;
    std::string name;
    LogosParser::LogosFileContext* fileCtx;

    std::unique_ptr<antlr4::ANTLRInputStream> input;
    std::unique_ptr<LogosLexer> lexer;
    std::unique_ptr<antlr4::CommonTokenStream> tokens;
    std::unique_ptr<LogosParser> parser;

    explicit LogosFile(const std::string& code, const std::filesystem::path& filePath);
    void parseFile();
    ~LogosFile();
};

#endif //LOGOSFILE_H
