#include "LogosFile.h"
#include "LogosLexer.h"
#include "SemAnalyser.h"

#include <ANTLRInputStream.h>

LogosFile::LogosFile(const std::string &code, const std::filesystem::path &path) {
    this->code = code;
    this->path = absolute(path).string();
    this->name = path.filename();
    this->fileCtx = nullptr;
}

void LogosFile::parseFile() {
    std::cout << "Parsing: " << name << std::endl;
    antlr4::ANTLRInputStream input(code);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    fileCtx = parser.logosFile();
}
