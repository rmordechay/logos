#include "Symbol.h"

#include <atn/PredictionContext.h>

Symbol::Symbol(const std::string& varName, const std::string& typeName, const SymbolType kind) {
    this->varName = varName;
    this->typeName = typeName;
    this->kind = kind;
    this->value = nullptr;
}

Symbol::Symbol(const std::string& varName, const SymbolType kind) {
    this->varName = varName;
    this->kind = kind;
    this->value = nullptr;
}
