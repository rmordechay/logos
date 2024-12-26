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
    void *value;

    explicit Symbol(const std::string& varName, const std::string& typeName, SymbolType kind);
};


#endif //SYMBOL_H
