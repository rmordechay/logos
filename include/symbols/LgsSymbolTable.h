#pragma once
#include "LgsSymbol.h"

class LgsErrHandler;

struct LgsSymbolTable {
    map<string, LgsSymbol> symbols;

    LgsSymbol* getSymbol(const string& name);
    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void addSymbol(const string& name, const LgsSymbol& symbol);
    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr);
    ~LgsSymbolTable() = default;
};
