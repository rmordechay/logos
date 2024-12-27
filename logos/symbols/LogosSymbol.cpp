#include "LogosSymbol.h"

#include <atn/PredictionContext.h>

LogosSymbol::LogosSymbol(const std::string& variableName, const std::string& typeName, const SymbolType kind) {
    this->variableName = variableName;
    this->typeName = typeName;
    this->kind = kind;
    this->value = nullptr;
}

LogosSymbol::LogosSymbol(const std::string& varName, const SymbolType kind) {
    this->variableName = varName;
    this->kind = kind;
    this->value = nullptr;
}
