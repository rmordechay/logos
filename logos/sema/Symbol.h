#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>

enum SymbolType {
    FIELD,
    LOCAL_VARIABLE,
    FUNCTION,
};

class Symbol {
public:
    std::string varName;
    std::string typeName;
    SymbolType kind;

    explicit Symbol(const std::string& name, const std::string& type, const SymbolType kind):
    varName(name), typeName(type), kind(kind) {}
};


#endif //SYMBOL_H
