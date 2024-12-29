#include "LogosFile.h"
#include "SemAnalyser.h"
#include "LogosSymbol.h"

#include <ANTLRInputStream.h>

LogosFile::LogosFile(const std::string& code, const std::filesystem::path& filePath) {
    this->code = code;
    this->path = absolute(filePath).string();
    this->name = filePath.filename();
    this->fileCtx = nullptr;
}

void LogosFile::setParser() {
    input = std::make_unique<antlr4::ANTLRInputStream>(code);
    lexer = std::make_unique<LogosLexer>(input.get());
    tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
    parser = std::make_unique<LogosParser>(tokens.get());
}

void LogosFile::parseFile() {
    setParser();
    fileCtx = parser->logosFile();
}

void LogosFile::addSymbols() {

}

LogosFile::~LogosFile() {
    delete fileCtx;
}
