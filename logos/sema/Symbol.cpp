#include "Symbol.h"

Symbol::Symbol(const std::string& varName, const std::string& typeName, const SymbolType kind) {
    this->varName = varName;
    this->typeName = typeName;
    this->kind = kind;
}
