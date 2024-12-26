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
    union {
        int intValue;
        float floatValue;
    };

    explicit Symbol(const std::string& varName, const std::string& typeName, SymbolType kind);
};


#endif //SYMBOL_H
