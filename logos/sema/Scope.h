#ifndef SCOPE_H
#define SCOPE_H
#include <map>


class Symbol;

class Scope {
public:
    std::map<std::string, Symbol*> symbolTable;
    explicit Scope();
};


#endif //SCOPE_H
