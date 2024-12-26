#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "Symbol.h"


#include <map>
#include <vector>

class SymbolTable {
public:
    std::map<std::string, Symbol*> symbols;
};



#endif //SYMBOLTABLE_H
