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
    addSymbols();
}

void LogosFile::addSymbols() {
    const auto objectFile = fileCtx->objectFile();
    if (objectFile != nullptr) {
        for (const auto explicitVarDec : objectFile->explicitVarDec()) {
            auto varName = explicitVarDec->VARIABLE()->getText();
            auto typeName = explicitVarDec->TYPE()->getText();
            symbolTable[varName] = new LogosSymbol(varName, typeName, FIELD);
        }
        for (const auto func : objectFile->funcImplementation()) {
            auto varName = func->funcDec()->VARIABLE()->getText();
            auto typeName = func->funcDec()->TYPE()->getText();
            symbolTable[varName] = new LogosSymbol(varName, typeName, FUNC_DEFINITION);
        }
    }
}

LogosFile::~LogosFile() {
    delete fileCtx;
}
