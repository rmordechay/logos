#include "LogosSymbol.h"

#include <atn/PredictionContext.h>

LogosSymbol::LogosSymbol(const std::string& variableName, const std::string& typeName, const SymbolKind kind) {
    this->variableName = variableName;
    this->typeName = typeName;
    this->kind = kind;
    this->logosValue = nullptr;
}

LogosSymbol::LogosSymbol(const std::string& varName, const SymbolKind kind) {
    this->variableName = varName;
    this->kind = kind;
    this->logosValue = nullptr;
}
