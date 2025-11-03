#pragma once
#include "LgsSymbol.h"
#include <map>

class LgsErrHandler;

struct LgsSymbolTable {
   std::map<std::string, LgsSymbol> symbols;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};
