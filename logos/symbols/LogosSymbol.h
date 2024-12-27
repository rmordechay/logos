#ifndef SYMBOL_H
#define SYMBOL_H
#include "LogosValue.h"


#include <string>

enum SymbolType {
    FIELD,
    LOCAL_VARIABLE,
    FUNCTION,
};

class LogosSymbol {
public:
    std::string variableName;
    std::string typeName;
    SymbolType kind;
    LogosValue *value;

    LogosSymbol(const std::string& variableName, const std::string& typeName, SymbolType kind);
    LogosSymbol(const std::string& varName, SymbolType kind);
};


#endif //SYMBOL_H
