#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>

class Symbol {
public:
    explicit Symbol(const std::string &name);
    std::string name;
};


#endif //SYMBOL_H
