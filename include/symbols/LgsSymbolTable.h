#pragma once
#include "LgsSymbol.h"
#include <map>

class LgsApp;
class LgsErrHandler;

struct LgsSymbolTable {
    std::unordered_map<std::string, LgsSymbol> symbols;
    std::unordered_map<std::string, LgsApp*> imports;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};
