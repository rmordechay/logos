#pragma once
#include "LgsSymbol.h"

class LgsErrHandler;

struct LgsSymbolTable {
    map<string, LgsSymbol> symbols;

    LgsSymbol* getSymbol(const string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void freeSymbols();
    ~LgsSymbolTable() = default;
};
