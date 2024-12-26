#ifndef SYMBOL_H
#define SYMBOL_H
#include "LogosValue.h"


#include <string>

enum SymbolType {
    FIELD,
    LOCAL_VARIABLE,
    FUNCTION,
};

class Symbol {
public:
    std::string varibaleName;
    std::string typeName;
    SymbolType kind;
    LogosValue *value;

    Symbol(const std::string& variableName, const std::string& typeName, SymbolType kind);
    Symbol(const std::string& varName, SymbolType kind);
};


#endif //SYMBOL_H
