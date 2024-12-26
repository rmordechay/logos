#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>

class Symbol {
public:
    std::string varName;
    std::string typeName;

    explicit Symbol(const std::string& name, const std::string& type);
};


#endif //SYMBOL_H
