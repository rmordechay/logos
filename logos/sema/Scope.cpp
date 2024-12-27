#include "Scope.h"

#include <map>

Scope::Scope() {}

LogosSymbol* Scope::resolveSymbol(const std::string& symbolName) {
    const auto it = symbolTable.find(symbolName);
    if (it == symbolTable.end()) {
        return nullptr;
    }
    return it->second;
}
