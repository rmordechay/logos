#include "LogosFile.h"
#include "SemAnalyser.h"

#include <ANTLRInputStream.h>

LogosFile::LogosFile(const std::string& code, const std::filesystem::path& filePath) {
    this->code = code;
    this->name = filePath.filename();
    this->fileCtx = nullptr;
}

void LogosFile::parseFile() {
    const auto input = std::make_unique<antlr4::ANTLRInputStream>(code);
    const auto lexer = std::make_unique<LogosLexer>(input.get());
    const auto tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
    const auto parser = std::make_unique<LogosParser>(tokens.get());
    fileCtx = parser->logosFile();
}

LogosFile::~LogosFile() {
    delete fileCtx;
}
