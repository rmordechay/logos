#ifndef SYMBOL_H
#define SYMBOL_H
#include "LogosType.h"


#include <string>

enum SymbolKind {
    FIELD,
    LOCAL_VARIABLE,
    FUNC_CALL,
    FUNC_DEFINITION,
    PARAM,
};

class LogosSymbol {
public:
    std::string variableName;
    std::string typeName;
    SymbolKind kind;
    LogosType *logosValue;

    LogosSymbol(const std::string& variableName, const std::string& typeName, SymbolKind kind);
    LogosSymbol(const std::string& varName, SymbolKind kind);
};


#endif //SYMBOL_H
