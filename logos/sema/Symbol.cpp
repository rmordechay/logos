#include "Symbol.h"

#include <atn/PredictionContext.h>

Symbol::Symbol(const std::string& variableName, const std::string& typeName, const SymbolType kind) {
    this->varibaleName = variableName;
    this->typeName = typeName;
    this->kind = kind;
    this->value = nullptr;
}

Symbol::Symbol(const std::string& varName, const SymbolType kind) {
    this->varibaleName = varName;
    this->kind = kind;
    this->value = nullptr;
}
