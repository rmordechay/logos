#ifndef SCOPE_H
#define SCOPE_H
#include <map>


class LogosSymbol;

class Scope {
public:
    std::map<std::string, LogosSymbol*> symbolTable;
    explicit Scope();
};


#endif //SCOPE_H
