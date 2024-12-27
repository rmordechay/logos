#ifndef SCOPE_H
#define SCOPE_H
#include <map>


class LogosSymbol;

class Scope {
public:
    std::map<std::string, LogosSymbol*> symbolTable;
    explicit Scope();

    LogosSymbol* resolveSymbol(const std::string& symbolName);
};


#endif //SCOPE_H
