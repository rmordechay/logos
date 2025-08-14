#pragma once
#include "LgsSymbol.h"

class LgsErrHandler;

struct LgsSymbolTable {
   std::map<std::string, LgsSymbol> symbols;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void freeSymbols();
    ~LgsSymbolTable() = default;
};
